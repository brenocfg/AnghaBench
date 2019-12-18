#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* j_common_ptr ;
struct TYPE_8__ {int /*<<< orphan*/  (* Printf ) (int /*<<< orphan*/ ,char*,char*) ;} ;
struct TYPE_7__ {TYPE_1__* err; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* format_message ) (TYPE_2__*,char*) ;} ;

/* Variables and functions */
 int JMSG_LENGTH_MAX ; 
 int /*<<< orphan*/  PRINT_ALL ; 
 TYPE_4__ ri ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void R_JPGOutputMessage(j_common_ptr cinfo)
{
  char buffer[JMSG_LENGTH_MAX];
  
  /* Create the message */
  (*cinfo->err->format_message) (cinfo, buffer);
  
  /* Send it to stderr, adding a newline */
  ri.Printf(PRINT_ALL, "%s\n", buffer);
}