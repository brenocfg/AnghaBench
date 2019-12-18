#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct queue {int id; int len; scalar_t__ live; struct queue* next; TYPE_1__* wh; } ;
struct params {int buddy_got; struct queue* q; int /*<<< orphan*/  state; int /*<<< orphan*/  tap; scalar_t__ buddy_data; } ;
struct iovec {char* iov_base; int iov_len; } ;
typedef  int /*<<< orphan*/  mac ;
typedef  int /*<<< orphan*/  iov ;
struct TYPE_2__ {int* i_fc; int /*<<< orphan*/  i_addr3; int /*<<< orphan*/  i_addr1; int /*<<< orphan*/  i_addr2; } ;

/* Variables and functions */
 int IEEE80211_FC1_DIR_TODS ; 
 int /*<<< orphan*/  S_START ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  buddy_get (struct params*,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  send_queue (struct params*) ; 
 int writev (int /*<<< orphan*/ ,struct iovec*,int) ; 

void read_buddy_data(struct params *p)
{
	unsigned short *ptr = (unsigned short*) p->buddy_data;
	int id, len, rem;
	struct queue *q = p->q;
	struct queue *last = p->q;
	char mac[12];
	struct iovec iov[2];

	id = ntohs(*ptr++);
	len = ntohs(*ptr++);

	rem = len + 4 - p->buddy_got;

	assert(rem > 0);
	if (!buddy_get(p, rem))
		return;

	/* w00t, got it */
#if 0	
	printf("id=%d len=%d\n", id, len);
#endif	
	p->buddy_got = 0;

	/* feedback loop bullshit */
	if (!q)
		return;
	if (!q->live)
		return;

	/* sanity chex */
	if (q->id != id) {
		printf("Diff ID\n");
		return;
	}

	rem = q->len - sizeof(*q->wh) - 4 - 4;
	if (rem != len) {
		printf("Diff len\n");
		return;
	}

	/* tap */
	if (q->wh->i_fc[1] & IEEE80211_FC1_DIR_TODS) {
		memcpy(mac, q->wh->i_addr3, 6);
		memcpy(&mac[6], q->wh->i_addr2, 6);
	} else {
		memcpy(mac, q->wh->i_addr1, 6);
		memcpy(&mac[6], q->wh->i_addr3, 6);
	}
	iov[0].iov_base = mac;
	iov[0].iov_len = sizeof(mac);
	iov[1].iov_base = (char*)ptr + 8 - 2;
	iov[1].iov_len = len - 8 + 2;

	rem = writev(p->tap, iov, sizeof(iov)/sizeof(struct iovec));
	if (rem == -1)
		err(1, "writev()");
	if (rem != (14+(len-8))) {
		printf("Short write %d\n", rem);
		exit(1);
	}

	/* deque */
	q->live = 0;
	if (q->next) {

		p->q = q->next;

		while (last) {
			if (!last->next) {
				last->next = q;
				q->next = 0;
				break;
			}
			last = last->next;
		}
	}
	
	/* drain queue */
	p->state = S_START;
	if (p->q->live)
		send_queue(p);
}