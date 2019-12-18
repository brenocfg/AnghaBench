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
struct tac_handle {int fd; char* errmsg; int /*<<< orphan*/  srvr_data; int /*<<< orphan*/  srvr_msg; int /*<<< orphan*/ * srvr_avs; int /*<<< orphan*/ * avs; int /*<<< orphan*/  user_msg; int /*<<< orphan*/  data; int /*<<< orphan*/  rem_addr; int /*<<< orphan*/  port; int /*<<< orphan*/  user; scalar_t__ cur_server; scalar_t__ num_servers; } ;

/* Variables and functions */
 int MAXAVPAIRS ; 
 int /*<<< orphan*/  init_clnt_str (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_srvr_str (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  srandomdev () ; 

struct tac_handle *
tac_open(void)
{
	int i;
	struct tac_handle *h;

	h = (struct tac_handle *)malloc(sizeof(struct tac_handle));
	if (h != NULL) {
		h->fd = -1;
		h->num_servers = 0;
		h->cur_server = 0;
		h->errmsg[0] = '\0';
		init_clnt_str(&h->user);
		init_clnt_str(&h->port);
		init_clnt_str(&h->rem_addr);
		init_clnt_str(&h->data);
		init_clnt_str(&h->user_msg);
		for (i=0; i<MAXAVPAIRS; i++) {
			init_clnt_str(&(h->avs[i]));
			init_srvr_str(&(h->srvr_avs[i]));
		}
		init_srvr_str(&h->srvr_msg);
		init_srvr_str(&h->srvr_data);
		srandomdev();
	}
	return h;
}