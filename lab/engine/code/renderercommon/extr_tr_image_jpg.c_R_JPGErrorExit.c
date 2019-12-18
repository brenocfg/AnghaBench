#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  setjmp_buffer; } ;
typedef  TYPE_2__ q_jpeg_error_mgr_t ;
typedef  TYPE_3__* j_common_ptr ;
struct TYPE_10__ {int /*<<< orphan*/  (* Printf ) (int /*<<< orphan*/ ,char*,char*) ;} ;
struct TYPE_9__ {TYPE_1__* err; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* format_message ) (TYPE_3__*,char*) ;} ;

/* Variables and functions */
 int JMSG_LENGTH_MAX ; 
 int /*<<< orphan*/  PRINT_ALL ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 TYPE_5__ ri ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void R_JPGErrorExit(j_common_ptr cinfo)
{
  char buffer[JMSG_LENGTH_MAX];

  /* cinfo->err really points to a q_jpeg_error_mgr_s struct, so coerce pointer */
  q_jpeg_error_mgr_t *jerr = (q_jpeg_error_mgr_t *)cinfo->err;
  
  (*cinfo->err->format_message) (cinfo, buffer);

  ri.Printf(PRINT_ALL, "Error: %s", buffer);

  /* Return control to the setjmp point */
  longjmp(jerr->setjmp_buffer, 1);
}