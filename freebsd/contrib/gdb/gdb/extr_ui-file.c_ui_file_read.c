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
struct ui_file {long (* to_read ) (struct ui_file*,char*,long) ;} ;

/* Variables and functions */
 long stub1 (struct ui_file*,char*,long) ; 

long
ui_file_read (struct ui_file *file, char *buf, long length_buf)
{
  return file->to_read (file, buf, length_buf); 
}