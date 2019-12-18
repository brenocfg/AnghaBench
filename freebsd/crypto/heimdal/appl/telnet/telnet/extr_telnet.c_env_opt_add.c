#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
#define  ENV_ESC 132 
#define  ENV_USERVAR 131 
#define  IAC 130 
#define  NEW_ENV_VALUE 129 
#define  NEW_ENV_VAR 128 
 int /*<<< orphan*/  OPT_REPLY_SIZE ; 
 scalar_t__ TELOPT_OLD_ENVIRON ; 
 unsigned char* env_default (int,int) ; 
 unsigned char* env_getvalue (unsigned char*) ; 
 int /*<<< orphan*/  old_env_value ; 
 int /*<<< orphan*/  old_env_var ; 
 int /*<<< orphan*/ * opt_reply ; 
 int /*<<< orphan*/ * opt_replyend ; 
 int /*<<< orphan*/ * opt_replyp ; 
 scalar_t__ opt_welldefined (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 void* realloc (int /*<<< orphan*/ *,int) ; 
 int strlen (char*) ; 
 scalar_t__ telopt_environ ; 

void
env_opt_add(unsigned char *ep)
{
	unsigned char *vp, c;

	if (opt_reply == NULL)		/*XXX*/
		return;			/*XXX*/

	if (ep == NULL || *ep == '\0') {
		/* Send user defined variables first. */
		env_default(1, 0);
		while ((ep = env_default(0, 0)))
			env_opt_add(ep);

		/* Now add the list of well know variables.  */
		env_default(1, 1);
		while ((ep = env_default(0, 1)))
			env_opt_add(ep);
		return;
	}
	vp = env_getvalue(ep);
        if (opt_replyp + (vp ? 2 * strlen((char *)vp) : 0) +
                                2 * strlen((char *)ep) + 6 > opt_replyend)
        {
		int len;
		void *tmp;
		opt_replyend += OPT_REPLY_SIZE;
		len = opt_replyend - opt_reply;
		tmp = realloc(opt_reply, len);
		if (tmp == NULL) {
/*@*/			printf("env_opt_add: realloc() failed!!!\n");
			opt_reply = opt_replyp = opt_replyend = NULL;
			return;
		}
		opt_reply = tmp;
		opt_replyp = opt_reply + len - (opt_replyend - opt_replyp);
		opt_replyend = opt_reply + len;
	}
	if (opt_welldefined((char *)ep)) {
#ifdef	OLD_ENVIRON
		if (telopt_environ == TELOPT_OLD_ENVIRON)
			*opt_replyp++ = old_env_var;
		else
#endif
			*opt_replyp++ = NEW_ENV_VAR;
	} else
		*opt_replyp++ = ENV_USERVAR;
	for (;;) {
		while ((c = *ep++)) {
			if (opt_replyp + (2 + 2) > opt_replyend)
				return;
			switch(c&0xff) {
			case IAC:
				*opt_replyp++ = IAC;
				break;
			case NEW_ENV_VAR:
			case NEW_ENV_VALUE:
			case ENV_ESC:
			case ENV_USERVAR:
				*opt_replyp++ = ENV_ESC;
				break;
			}
			*opt_replyp++ = c;
		}
		if ((ep = vp)) {
			if (opt_replyp + (1 + 2 + 2) > opt_replyend)
				return;
#ifdef	OLD_ENVIRON
			if (telopt_environ == TELOPT_OLD_ENVIRON)
				*opt_replyp++ = old_env_value;
			else
#endif
				*opt_replyp++ = NEW_ENV_VALUE;
			vp = NULL;
		} else
			break;
	}
}