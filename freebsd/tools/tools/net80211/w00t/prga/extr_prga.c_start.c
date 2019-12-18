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
struct params {int prga_len; int mtu; int data_len; int /*<<< orphan*/  state; scalar_t__ frag; int /*<<< orphan*/  seq; scalar_t__ data_try; int /*<<< orphan*/  data; int /*<<< orphan*/  data_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_SEND_FRAG ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void start(struct params *p)
{
	int len;

	len = p->prga_len;
	len -= 4;
	assert(len > 0);

	len *= 4;
	if (len > p->mtu)
		len = p->mtu;

	p->data_len = len;
	memset(p->data, 0, p->data_len);
	memcpy(p->data, "\xaa\xaa\x03\x00\x00\x00\x08\x06", 8);
	p->data_ptr = p->data;
	p->data_try = 0;
	p->seq++;
	p->frag = 0;
	p->state = S_SEND_FRAG;
}