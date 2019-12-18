#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* dbg; } ;
typedef  TYPE_2__ mrdb_state ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_4__ {int /*<<< orphan*/  irep; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* build_path (int /*<<< orphan*/ *,char const*,char const*) ; 
 char* dirname (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  mrb_debug_get_filename (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_free (int /*<<< orphan*/ *,void*) ; 
 char* strrchr (char const*,char) ; 

char*
mrb_debug_get_source(mrb_state *mrb, mrdb_state *mrdb, const char *srcpath, const char *filename)
{
  int i;
  FILE *fp;
  const char *search_path[3];
  char *path = NULL;
  const char *srcname = strrchr(filename, '/');

  if (srcname) srcname++;
  else srcname = filename;

  search_path[0] = srcpath;
  search_path[1] = dirname(mrb, mrb_debug_get_filename(mrdb->dbg->irep, 0));
  search_path[2] = ".";

  for (i = 0; i < 3; i++) {
    if (search_path[i] == NULL) {
      continue;
    }

    if ((path = build_path(mrb, search_path[i], srcname)) == NULL) {
      continue;
    }

    if ((fp = fopen(path, "rb")) == NULL) {
      mrb_free(mrb, path);
      path = NULL;
      continue;
    }
    fclose(fp);
    break;
  }

  mrb_free(mrb, (void *)search_path[1]);

  return path;
}