#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ static_file_idx; scalar_t__ static_file_max_len; char const** static_files; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (char const**) ; 
 TYPE_1__ conf ; 
 scalar_t__ strlen (char const*) ; 

void
set_default_static_files (void)
{
  size_t i;
  const char *exts[] = {
    ".css",
    ".js ",
    ".jpg",
    ".png",
    ".gif",
    ".ico",
    ".jpeg",
    ".pdf",
    ".txt",
    ".csv",
    ".mpeg",
    ".mpg",
    ".swf",
    ".woff",
    ".woff2",
    ".xls",
    ".xlsx",
    ".doc ",
    ".docx",
    ".ppt ",
    ".pptx",
    ".zip",
    ".mp3",
    ".mp4",
    ".exe",
    ".iso ",
    ".gz  ",
    ".rar ",
    ".svg ",
    ".bmp ",
    ".tar ",
    ".tgz ",
    ".tiff",
    ".tif ",
    ".ttf ",
    ".flv ",
  };

  if (conf.static_file_idx > 0)
    return;

  for (i = 0; i < ARRAY_SIZE (exts); i++) {
    if (conf.static_file_max_len < strlen (exts[i]))
      conf.static_file_max_len = strlen (exts[i]);
    conf.static_files[conf.static_file_idx++] = exts[i];
  }
}