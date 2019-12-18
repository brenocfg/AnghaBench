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
struct l_ipc_perm {scalar_t__ uid; scalar_t__ gid; scalar_t__ cuid; scalar_t__ cgid; scalar_t__ mode; int /*<<< orphan*/  seq; int /*<<< orphan*/  key; } ;
struct l_ipc64_perm {scalar_t__ uid; scalar_t__ gid; scalar_t__ cuid; scalar_t__ cgid; scalar_t__ mode; int /*<<< orphan*/  seq; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int EOVERFLOW ; 

__attribute__((used)) static int
linux_ipc64_perm_to_ipc_perm(struct l_ipc64_perm *in, struct l_ipc_perm *out)
{

	out->key = in->key;
	out->uid = in->uid;
	out->gid = in->gid;
	out->cuid = in->cuid;
	out->cgid = in->cgid;
	out->mode = in->mode;
	out->seq = in->seq;

	/* Linux does not check overflow */
	if (out->uid != in->uid || out->gid != in->gid ||
	    out->cuid != in->cuid || out->cgid != in->cgid ||
	    out->mode != in->mode)
		return (EOVERFLOW);
	else
		return (0);
}