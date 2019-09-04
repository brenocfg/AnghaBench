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
 int /*<<< orphan*/  strbuf_add (struct strbuf*,void const*,size_t) ; 

__attribute__((used)) static int write_strbuf(void *user_data, const void *data, size_t len)
{
	struct strbuf *sb = user_data;
	strbuf_add(sb, data, len);
	return len;
}