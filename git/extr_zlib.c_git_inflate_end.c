#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* msg; } ;
struct TYPE_6__ {TYPE_4__ z; } ;
typedef  TYPE_1__ git_zstream ;

/* Variables and functions */
 int Z_OK ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,char*) ; 
 int inflateEnd (TYPE_4__*) ; 
 int /*<<< orphan*/  zerr_to_string (int) ; 
 int /*<<< orphan*/  zlib_post_call (TYPE_1__*) ; 
 int /*<<< orphan*/  zlib_pre_call (TYPE_1__*) ; 

void git_inflate_end(git_zstream *strm)
{
	int status;

	zlib_pre_call(strm);
	status = inflateEnd(&strm->z);
	zlib_post_call(strm);
	if (status == Z_OK)
		return;
	error("inflateEnd: %s (%s)", zerr_to_string(status),
	      strm->z.msg ? strm->z.msg : "no message");
}