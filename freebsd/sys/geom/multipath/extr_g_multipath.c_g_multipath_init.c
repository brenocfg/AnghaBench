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
struct g_class {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  bioq_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_multipath_kt ; 
 int /*<<< orphan*/  gmtbq ; 
 int /*<<< orphan*/  gmtbq_mtx ; 
 int /*<<< orphan*/  kproc_create (int /*<<< orphan*/ ,struct g_class*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_multipath_init(struct g_class *mp)
{
	bioq_init(&gmtbq);
	mtx_init(&gmtbq_mtx, "gmtbq", NULL, MTX_DEF);
	kproc_create(g_multipath_kt, mp, NULL, 0, 0, "g_mp_kt");
}