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
struct TYPE_3__ {scalar_t__ stdio_out; } ;
typedef  TYPE_1__ process_info_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int _O_RDONLY ; 
 int _O_TEXT ; 
 int /*<<< orphan*/  _close (int) ; 
 int /*<<< orphan*/ * _fdopen (int,char*) ; 
 int _open_osfhandle (intptr_t,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_lines (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 

int process_copy_output(process_info_t* p, FILE* stream) {
  char buf[1024];
  int fd, r;
  FILE* f;

  fd = _open_osfhandle((intptr_t)p->stdio_out, _O_RDONLY | _O_TEXT);
  if (fd == -1)
    return -1;
  f = _fdopen(fd, "rt");
  if (f == NULL) {
    _close(fd);
    return -1;
  }

  r = fseek(f, 0, SEEK_SET);
  if (r < 0)
    return -1;

  while (fgets(buf, sizeof(buf), f) != NULL)
    print_lines(buf, strlen(buf), stream);

  if (ferror(f))
    return -1;

  fclose(f);
  return 0;
}