#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  z; } ;
typedef  TYPE_1__ git_zstream ;

/* Variables and functions */
 int deflateEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zlib_post_call (TYPE_1__*) ; 
 int /*<<< orphan*/  zlib_pre_call (TYPE_1__*) ; 

int git_deflate_abort(git_zstream *strm)
{
	int status;

	zlib_pre_call(strm);
	status = deflateEnd(&strm->z);
	zlib_post_call(strm);
	return status;
}