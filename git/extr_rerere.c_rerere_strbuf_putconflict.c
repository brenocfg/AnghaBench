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
struct strbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addchars (struct strbuf*,int,size_t) ; 

__attribute__((used)) static void rerere_strbuf_putconflict(struct strbuf *buf, int ch, size_t size)
{
	strbuf_addchars(buf, ch, size);
	strbuf_addch(buf, '\n');
}