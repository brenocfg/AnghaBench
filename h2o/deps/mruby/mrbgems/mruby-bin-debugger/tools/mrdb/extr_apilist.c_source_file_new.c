#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int lineno; char* path; int /*<<< orphan*/ * fp; } ;
typedef  TYPE_1__ source_file ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_debug_context ;

/* Variables and functions */
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,char,int) ; 
 scalar_t__ mrb_malloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  source_file_free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static source_file*
source_file_new(mrb_state *mrb, mrb_debug_context *dbg, char *filename)
{
  source_file *file;

  file = (source_file*)mrb_malloc(mrb, sizeof(source_file));

  memset(file, '\0', sizeof(source_file));
  file->fp = fopen(filename, "rb");

  if (file->fp == NULL) {
    source_file_free(mrb, file);
    return NULL;
  }

  file->lineno = 1;
  file->path = (char*)mrb_malloc(mrb, strlen(filename) + 1);
  strcpy(file->path, filename);
  return file;
}