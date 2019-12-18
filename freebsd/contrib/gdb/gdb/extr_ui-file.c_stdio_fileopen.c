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
struct ui_file {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct ui_file* stdio_file_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct ui_file *
stdio_fileopen (FILE *file)
{
  return stdio_file_new (file, 0);
}