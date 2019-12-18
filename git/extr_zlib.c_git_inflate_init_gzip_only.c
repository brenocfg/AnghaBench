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
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ,char*) ; 
 int inflateInit2 (TYPE_4__*,int const) ; 
 int /*<<< orphan*/  zerr_to_string (int) ; 
 int /*<<< orphan*/  zlib_post_call (TYPE_1__*) ; 
 int /*<<< orphan*/  zlib_pre_call (TYPE_1__*) ; 

void git_inflate_init_gzip_only(git_zstream *strm)
{
	/*
	 * Use default 15 bits, +16 is to accept only gzip and to
	 * yield Z_DATA_ERROR when fed zlib format.
	 */
	const int windowBits = 15 + 16;
	int status;

	zlib_pre_call(strm);
	status = inflateInit2(&strm->z, windowBits);
	zlib_post_call(strm);
	if (status == Z_OK)
		return;
	die("inflateInit2: %s (%s)", zerr_to_string(status),
	    strm->z.msg ? strm->z.msg : "no message");
}