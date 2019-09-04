#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* msg; } ;
struct TYPE_7__ {TYPE_6__ z; } ;
typedef  TYPE_1__ git_zstream ;

/* Variables and functions */
 int Z_OK ; 
 int deflateInit (TYPE_6__*,int) ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zerr_to_string (int) ; 
 int /*<<< orphan*/  zlib_post_call (TYPE_1__*) ; 
 int /*<<< orphan*/  zlib_pre_call (TYPE_1__*) ; 

void git_deflate_init(git_zstream *strm, int level)
{
	int status;

	memset(strm, 0, sizeof(*strm));
	zlib_pre_call(strm);
	status = deflateInit(&strm->z, level);
	zlib_post_call(strm);
	if (status == Z_OK)
		return;
	die("deflateInit: %s (%s)", zerr_to_string(status),
	    strm->z.msg ? strm->z.msg : "no message");
}