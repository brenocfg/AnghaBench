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
struct lazy_dir_thread_data {int /*<<< orphan*/  lazy_entries; int /*<<< orphan*/  k_end; int /*<<< orphan*/  k_start; int /*<<< orphan*/  istate; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  handle_range_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void *lazy_dir_thread_proc(void *_data)
{
	struct lazy_dir_thread_data *d = _data;
	struct strbuf prefix = STRBUF_INIT;
	handle_range_1(d->istate, d->k_start, d->k_end, NULL, &prefix, d->lazy_entries);
	strbuf_release(&prefix);
	return NULL;
}