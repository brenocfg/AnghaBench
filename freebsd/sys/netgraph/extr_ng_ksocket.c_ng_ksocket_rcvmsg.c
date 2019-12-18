#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct thread {int dummy; } ;
struct sockopt {int sopt_valsize; int /*<<< orphan*/ * sopt_td; int /*<<< orphan*/  sopt_val; int /*<<< orphan*/  sopt_name; int /*<<< orphan*/  sopt_level; int /*<<< orphan*/  sopt_dir; } ;
struct socket {int so_state; int so_options; TYPE_2__* so_proto; } ;
struct sockaddr {int sa_len; } ;
struct TYPE_9__ {int typecookie; int const cmd; int arglen; int /*<<< orphan*/  token; } ;
struct ng_mesg {TYPE_3__ header; scalar_t__ data; } ;
struct ng_ksocket_sockopt {int /*<<< orphan*/  value; int /*<<< orphan*/  name; int /*<<< orphan*/  level; } ;
typedef  TYPE_4__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  void* ng_ID_t ;
typedef  int /*<<< orphan*/  item_p ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_10__ {int flags; void* response_addr; int /*<<< orphan*/  response_token; struct socket* so; } ;
struct TYPE_8__ {TYPE_1__* pr_usrreqs; } ;
struct TYPE_7__ {int (* pru_peeraddr ) (struct socket*,struct sockaddr**) ;int (* pru_sockaddr ) (struct socket*,struct sockaddr**) ;} ;

/* Variables and functions */
 int EALREADY ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENOTCONN ; 
 int ENXIO ; 
 int /*<<< orphan*/  ERROUT (int) ; 
 int EWOULDBLOCK ; 
 int KSF_ACCEPTING ; 
 int KSF_CONNECTING ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_SONAME ; 
 int /*<<< orphan*/  NGI_GET_MSG (int /*<<< orphan*/ ,struct ng_mesg*) ; 
 void* NGI_RETADDR (int /*<<< orphan*/ ) ; 
#define  NGM_KSOCKET_ACCEPT 136 
#define  NGM_KSOCKET_BIND 135 
#define  NGM_KSOCKET_CONNECT 134 
#define  NGM_KSOCKET_COOKIE 133 
#define  NGM_KSOCKET_GETNAME 132 
#define  NGM_KSOCKET_GETOPT 131 
#define  NGM_KSOCKET_GETPEERNAME 130 
#define  NGM_KSOCKET_LISTEN 129 
#define  NGM_KSOCKET_SETOPT 128 
 int /*<<< orphan*/  NG_FREE_MSG (struct ng_mesg*) ; 
 int NG_KSOCKET_MAX_OPTLEN ; 
 int /*<<< orphan*/  NG_MKRESPONSE (struct ng_mesg*,struct ng_mesg*,int,int /*<<< orphan*/ ) ; 
 TYPE_4__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_RESPOND_MSG (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ng_mesg*) ; 
 int SADATA_OFFSET ; 
 int /*<<< orphan*/  SOPT_GET ; 
 int /*<<< orphan*/  SOPT_SET ; 
 int SO_ACCEPTCONN ; 
 int SS_ISCONFIRMING ; 
 int SS_ISCONNECTED ; 
 int SS_ISCONNECTING ; 
 int SS_NBIO ; 
 int /*<<< orphan*/  bcopy (struct sockaddr*,scalar_t__,int) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  free (struct sockaddr*,int /*<<< orphan*/ ) ; 
 int ng_ksocket_accept (TYPE_4__* const) ; 
 int sobind (struct socket* const,struct sockaddr* const,struct thread*) ; 
 int soconnect (struct socket* const,struct sockaddr* const,struct thread*) ; 
 int sogetopt (struct socket* const,struct sockopt*) ; 
 int solisten (struct socket* const,int /*<<< orphan*/ ,struct thread*) ; 
 int sosetopt (struct socket* const,struct sockopt*) ; 
 int stub1 (struct socket* const,struct sockaddr**) ; 

__attribute__((used)) static int
ng_ksocket_rcvmsg(node_p node, item_p item, hook_p lasthook)
{
	struct thread *td = curthread;	/* XXX broken */
	const priv_p priv = NG_NODE_PRIVATE(node);
	struct socket *const so = priv->so;
	struct ng_mesg *resp = NULL;
	int error = 0;
	struct ng_mesg *msg;
	ng_ID_t raddr;

	NGI_GET_MSG(item, msg);
	switch (msg->header.typecookie) {
	case NGM_KSOCKET_COOKIE:
		switch (msg->header.cmd) {
		case NGM_KSOCKET_BIND:
		    {
			struct sockaddr *const sa
			    = (struct sockaddr *)msg->data;

			/* Sanity check */
			if (msg->header.arglen < SADATA_OFFSET
			    || msg->header.arglen < sa->sa_len)
				ERROUT(EINVAL);
			if (so == NULL)
				ERROUT(ENXIO);

			/* Bind */
			error = sobind(so, sa, td);
			break;
		    }
		case NGM_KSOCKET_LISTEN:
		    {
			/* Sanity check */
			if (msg->header.arglen != sizeof(int32_t))
				ERROUT(EINVAL);
			if (so == NULL)
				ERROUT(ENXIO);

			/* Listen */
			so->so_state |= SS_NBIO;
			error = solisten(so, *((int32_t *)msg->data), td);
			break;
		    }

		case NGM_KSOCKET_ACCEPT:
		    {
			/* Sanity check */
			if (msg->header.arglen != 0)
				ERROUT(EINVAL);
			if (so == NULL)
				ERROUT(ENXIO);

			/* Make sure the socket is capable of accepting */
			if (!(so->so_options & SO_ACCEPTCONN))
				ERROUT(EINVAL);
			if (priv->flags & KSF_ACCEPTING)
				ERROUT(EALREADY);

			/*
			 * If a connection is already complete, take it.
			 * Otherwise let the upcall function deal with
			 * the connection when it comes in.
			 */
			error = ng_ksocket_accept(priv);
			if (error != 0 && error != EWOULDBLOCK)
				ERROUT(error);
			priv->response_token = msg->header.token;
			raddr = priv->response_addr = NGI_RETADDR(item);
			break;
		    }

		case NGM_KSOCKET_CONNECT:
		    {
			struct sockaddr *const sa
			    = (struct sockaddr *)msg->data;

			/* Sanity check */
			if (msg->header.arglen < SADATA_OFFSET
			    || msg->header.arglen < sa->sa_len)
				ERROUT(EINVAL);
			if (so == NULL)
				ERROUT(ENXIO);

			/* Do connect */
			if ((so->so_state & SS_ISCONNECTING) != 0)
				ERROUT(EALREADY);
			if ((error = soconnect(so, sa, td)) != 0) {
				so->so_state &= ~SS_ISCONNECTING;
				ERROUT(error);
			}
			if ((so->so_state & SS_ISCONNECTING) != 0) {
				/* We will notify the sender when we connect */
				priv->response_token = msg->header.token;
				raddr = priv->response_addr = NGI_RETADDR(item);
				priv->flags |= KSF_CONNECTING;
				ERROUT(EINPROGRESS);
			}
			break;
		    }

		case NGM_KSOCKET_GETNAME:
		case NGM_KSOCKET_GETPEERNAME:
		    {
			int (*func)(struct socket *so, struct sockaddr **nam);
			struct sockaddr *sa = NULL;
			int len;

			/* Sanity check */
			if (msg->header.arglen != 0)
				ERROUT(EINVAL);
			if (so == NULL)
				ERROUT(ENXIO);

			/* Get function */
			if (msg->header.cmd == NGM_KSOCKET_GETPEERNAME) {
				if ((so->so_state
				    & (SS_ISCONNECTED|SS_ISCONFIRMING)) == 0)
					ERROUT(ENOTCONN);
				func = so->so_proto->pr_usrreqs->pru_peeraddr;
			} else
				func = so->so_proto->pr_usrreqs->pru_sockaddr;

			/* Get local or peer address */
			if ((error = (*func)(so, &sa)) != 0)
				goto bail;
			len = (sa == NULL) ? 0 : sa->sa_len;

			/* Send it back in a response */
			NG_MKRESPONSE(resp, msg, len, M_NOWAIT);
			if (resp == NULL) {
				error = ENOMEM;
				goto bail;
			}
			bcopy(sa, resp->data, len);

		bail:
			/* Cleanup */
			if (sa != NULL)
				free(sa, M_SONAME);
			break;
		    }

		case NGM_KSOCKET_GETOPT:
		    {
			struct ng_ksocket_sockopt *ksopt =
			    (struct ng_ksocket_sockopt *)msg->data;
			struct sockopt sopt;

			/* Sanity check */
			if (msg->header.arglen != sizeof(*ksopt))
				ERROUT(EINVAL);
			if (so == NULL)
				ERROUT(ENXIO);

			/* Get response with room for option value */
			NG_MKRESPONSE(resp, msg, sizeof(*ksopt)
			    + NG_KSOCKET_MAX_OPTLEN, M_NOWAIT);
			if (resp == NULL)
				ERROUT(ENOMEM);

			/* Get socket option, and put value in the response */
			sopt.sopt_dir = SOPT_GET;
			sopt.sopt_level = ksopt->level;
			sopt.sopt_name = ksopt->name;
			sopt.sopt_td = NULL;
			sopt.sopt_valsize = NG_KSOCKET_MAX_OPTLEN;
			ksopt = (struct ng_ksocket_sockopt *)resp->data;
			sopt.sopt_val = ksopt->value;
			if ((error = sogetopt(so, &sopt)) != 0) {
				NG_FREE_MSG(resp);
				break;
			}

			/* Set actual value length */
			resp->header.arglen = sizeof(*ksopt)
			    + sopt.sopt_valsize;
			break;
		    }

		case NGM_KSOCKET_SETOPT:
		    {
			struct ng_ksocket_sockopt *const ksopt =
			    (struct ng_ksocket_sockopt *)msg->data;
			const int valsize = msg->header.arglen - sizeof(*ksopt);
			struct sockopt sopt;

			/* Sanity check */
			if (valsize < 0)
				ERROUT(EINVAL);
			if (so == NULL)
				ERROUT(ENXIO);

			/* Set socket option */
			sopt.sopt_dir = SOPT_SET;
			sopt.sopt_level = ksopt->level;
			sopt.sopt_name = ksopt->name;
			sopt.sopt_val = ksopt->value;
			sopt.sopt_valsize = valsize;
			sopt.sopt_td = NULL;
			error = sosetopt(so, &sopt);
			break;
		    }

		default:
			error = EINVAL;
			break;
		}
		break;
	default:
		error = EINVAL;
		break;
	}
done:
	NG_RESPOND_MSG(error, node, item, resp);
	NG_FREE_MSG(msg);
	return (error);
}