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
struct sbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_sbuf_integrity (struct sbuf*) ; 
 int /*<<< orphan*/  assert_sbuf_state (struct sbuf*,int /*<<< orphan*/ ) ; 
 int sbuf_bcat (struct sbuf*,void const*,size_t) ; 
 int /*<<< orphan*/  sbuf_clear (struct sbuf*) ; 

int
sbuf_bcpy(struct sbuf *s, const void *buf, size_t len)
{

	assert_sbuf_integrity(s);
	assert_sbuf_state(s, 0);

	sbuf_clear(s);
	return (sbuf_bcat(s, buf, len));
}