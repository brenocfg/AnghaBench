#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* msg; } ;
struct TYPE_6__ {TYPE_1__ z; } ;
typedef  TYPE_2__ git_zstream ;

/* Variables and functions */
 int Z_OK ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,char*) ; 
 int git_deflate_abort (TYPE_2__*) ; 
 int /*<<< orphan*/  zerr_to_string (int) ; 

void git_deflate_end(git_zstream *strm)
{
	int status = git_deflate_abort(strm);

	if (status == Z_OK)
		return;
	error("deflateEnd: %s (%s)", zerr_to_string(status),
	      strm->z.msg ? strm->z.msg : "no message");
}