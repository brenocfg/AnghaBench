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
 int /*<<< orphan*/  sbuf_put_bytes (struct sbuf*,char*,int) ; 

__attribute__((used)) static void
sbuf_put_byte(struct sbuf *s, char c)
{

	sbuf_put_bytes(s, &c, 1);
}