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
struct fst_session {struct fst_group* group; } ;
struct fst_group {int dummy; } ;

/* Variables and functions */

struct fst_group * fst_session_get_group(struct fst_session *s)
{
	return s->group;
}