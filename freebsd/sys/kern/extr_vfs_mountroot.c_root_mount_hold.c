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
struct root_hold_token {char const* who; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct root_hold_token*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TSHOLD (char*) ; 
 int /*<<< orphan*/  list ; 
 struct root_hold_token* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  root_holds ; 
 int /*<<< orphan*/  root_holds_mtx ; 

struct root_hold_token *
root_mount_hold(const char *identifier)
{
	struct root_hold_token *h;

	h = malloc(sizeof *h, M_DEVBUF, M_ZERO | M_WAITOK);
	h->who = identifier;
	mtx_lock(&root_holds_mtx);
	TSHOLD("root mount");
	LIST_INSERT_HEAD(&root_holds, h, list);
	mtx_unlock(&root_holds_mtx);
	return (h);
}