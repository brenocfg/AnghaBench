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
struct untracked_cache {int /*<<< orphan*/  ident; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_ident_string () ; 
 int /*<<< orphan*/  strbuf_addch (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void set_untracked_ident(struct untracked_cache *uc)
{
	strbuf_reset(&uc->ident);
	strbuf_addstr(&uc->ident, get_ident_string());

	/*
	 * This strbuf used to contain a list of NUL separated
	 * strings, so save NUL too for backward compatibility.
	 */
	strbuf_addch(&uc->ident, 0);
}