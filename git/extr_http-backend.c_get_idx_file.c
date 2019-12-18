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
 int /*<<< orphan*/  hdr_cache_forever (struct strbuf*) ; 
 int /*<<< orphan*/  select_getanyfile (struct strbuf*) ; 
 int /*<<< orphan*/  send_local_file (struct strbuf*,char*,char*) ; 

__attribute__((used)) static void get_idx_file(struct strbuf *hdr, char *name)
{
	select_getanyfile(hdr);
	hdr_cache_forever(hdr);
	send_local_file(hdr, "application/x-git-packed-objects-toc", name);
}