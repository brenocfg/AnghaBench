#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  void* u_char ;
struct TYPE_13__ {int /*<<< orphan*/  s; void* u; void* i; } ;
struct TYPE_14__ {int host_mode; int attr; TYPE_1__ value; int /*<<< orphan*/  group; void* peerversion; int /*<<< orphan*/  peerkey; void* ttl; void* maxpoll; void* minpoll; int /*<<< orphan*/  peerflags; int /*<<< orphan*/ * addr; } ;
typedef  TYPE_2__ peer_node ;
typedef  int /*<<< orphan*/  keyid_t ;
typedef  TYPE_2__ attr_val_fifo ;
typedef  TYPE_2__ attr_val ;
typedef  int /*<<< orphan*/  address_node ;

/* Variables and functions */
 int /*<<< orphan*/  APPEND_G_FIFO (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  CHECK_FIFO_CONSISTENCY (TYPE_2__) ; 
 void* KEYID_T_MAX ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 void* MAX_TTL ; 
 void* NTP_MAXPOLL ; 
 void* NTP_MINPOLL ; 
 void* NTP_VERSION ; 
#define  T_Flag 135 
#define  T_Ident 134 
#define  T_Key 133 
#define  T_Maxpoll 132 
#define  T_Minpoll 131 
#define  T_Mode 130 
#define  T_Ttl 129 
#define  T_Version 128 
 void* UCHAR_MAX ; 
 int /*<<< orphan*/  UNLINK_FIFO (TYPE_2__*,TYPE_2__,int /*<<< orphan*/ ) ; 
 TYPE_2__* emalloc_zero (int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  is_refclk_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  token_name (int) ; 

peer_node *
create_peer_node(
	int		hmode,
	address_node *	addr,
	attr_val_fifo *	options
	)
{
	peer_node *my_node;
	attr_val *option;
	int freenode;
	int errflag = 0;

	my_node = emalloc_zero(sizeof(*my_node));

	/* Initialize node values to default */
	my_node->peerversion = NTP_VERSION;

	/* Now set the node to the read values */
	my_node->host_mode = hmode;
	my_node->addr = addr;

	/*
	 * the options FIFO mixes items that will be saved in the
	 * peer_node as explicit members, such as minpoll, and
	 * those that are moved intact to the peer_node's peerflags
	 * FIFO.  The options FIFO is consumed and reclaimed here.
	 */

	if (options != NULL)
		CHECK_FIFO_CONSISTENCY(*options);
	while (options != NULL) {
		UNLINK_FIFO(option, *options, link);
		if (NULL == option) {
			free(options);
			break;
		}

		freenode = 1;
		/* Check the kind of option being set */
		switch (option->attr) {

		case T_Flag:
			APPEND_G_FIFO(my_node->peerflags, option);
			freenode = 0;
			break;

		case T_Minpoll:
			if (option->value.i < NTP_MINPOLL ||
			    option->value.i > UCHAR_MAX) {
				msyslog(LOG_INFO,
					"minpoll: provided value (%d) is out of range [%d-%d])",
					option->value.i, NTP_MINPOLL,
					UCHAR_MAX);
				my_node->minpoll = NTP_MINPOLL;
			} else {
				my_node->minpoll =
					(u_char)option->value.u;
			}
			break;

		case T_Maxpoll:
			if (option->value.i < 0 ||
			    option->value.i > NTP_MAXPOLL) {
				msyslog(LOG_INFO,
					"maxpoll: provided value (%d) is out of range [0-%d])",
					option->value.i, NTP_MAXPOLL);
				my_node->maxpoll = NTP_MAXPOLL;
			} else {
				my_node->maxpoll =
					(u_char)option->value.u;
			}
			break;

		case T_Ttl:
			if (is_refclk_addr(addr)) {
				msyslog(LOG_ERR, "'ttl' does not apply for refclocks");
				errflag = 1;
			} else if (option->value.u >= MAX_TTL) {
				msyslog(LOG_ERR, "ttl: invalid argument");
				errflag = 1;
			} else {
				my_node->ttl = (u_char)option->value.u;
			}
			break;

		case T_Mode:
			if (is_refclk_addr(addr)) {
				my_node->ttl = option->value.u;
			} else {
				msyslog(LOG_ERR, "'mode' does not apply for network peers");
				errflag = 1;
			}
			break;

		case T_Key:
			if (option->value.u >= KEYID_T_MAX) {
				msyslog(LOG_ERR, "key: invalid argument");
				errflag = 1;
			} else {
				my_node->peerkey =
					(keyid_t)option->value.u;
			}
			break;

		case T_Version:
			if (option->value.u >= UCHAR_MAX) {
				msyslog(LOG_ERR, "version: invalid argument");
				errflag = 1;
			} else {
				my_node->peerversion =
					(u_char)option->value.u;
			}
			break;

		case T_Ident:
			my_node->group = option->value.s;
			break;

		default:
			msyslog(LOG_ERR,
				"Unknown peer/server option token %s",
				token_name(option->attr));
			errflag = 1;
		}
		if (freenode)
			free(option);
	}

	/* Check if errors were reported. If yes, ignore the node */
	if (errflag) {
		free(my_node);
		my_node = NULL;
	}

	return my_node;
}