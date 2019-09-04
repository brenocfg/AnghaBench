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
typedef  int /*<<< orphan*/  git_packbuilder ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  PREPARE_PACK ; 
 int /*<<< orphan*/  git_buf_sanitize (int /*<<< orphan*/ *) ; 
 int write_pack (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_pack_buf ; 

int git_packbuilder_write_buf(git_buf *buf, git_packbuilder *pb)
{
	PREPARE_PACK;
	git_buf_sanitize(buf);
	return write_pack(pb, &write_pack_buf, buf);
}