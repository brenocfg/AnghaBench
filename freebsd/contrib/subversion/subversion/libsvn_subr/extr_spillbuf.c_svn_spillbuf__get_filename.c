#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char const* filename; } ;
typedef  TYPE_1__ svn_spillbuf_t ;

/* Variables and functions */

const char *
svn_spillbuf__get_filename(const svn_spillbuf_t *buf)
{
  return buf->filename;
}