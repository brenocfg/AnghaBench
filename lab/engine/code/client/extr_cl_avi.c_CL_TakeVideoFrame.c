#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  motionJpeg; int /*<<< orphan*/  eBuffer; int /*<<< orphan*/  cBuffer; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  fileOpen; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* TakeVideoFrame ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_2__ afd ; 
 TYPE_1__ re ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void CL_TakeVideoFrame( void )
{
  // AVI file isn't open
  if( !afd.fileOpen )
    return;

  re.TakeVideoFrame( afd.width, afd.height,
      afd.cBuffer, afd.eBuffer, afd.motionJpeg );
}