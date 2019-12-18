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
struct TYPE_2__ {int /*<<< orphan*/  type; scalar_t__ len; int /*<<< orphan*/  ptr; } ;
struct parse {long long len; TYPE_1__ lex; int /*<<< orphan*/  text; scalar_t__ line_pos; scalar_t__ line; scalar_t__ pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  lex_none ; 
 long long lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 long long read (int,int /*<<< orphan*/ ,long long) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  zmalloc (long long) ; 

struct parse *tl_init_parse_file (const char *fname) {
  int fd = open (fname, O_RDONLY);
  if (fd < 0) {
    fprintf (stderr, "Error %m\n");
    assert (0);
    return 0;
  }
  long long size = lseek (fd, 0, SEEK_END);
  if (size <= 0) {
    fprintf (stderr, "size is %lld. Too small.\n", size);
    return 0;
  }
  static struct parse save;
  save.text = zmalloc (size);
  lseek (fd, 0, SEEK_SET);
  save.len = read (fd, save.text, size);
  assert (save.len == size);
  save.pos = 0;
  save.line = 0;
  save.line_pos = 0;
  save.lex.ptr = save.text;
  save.lex.len = 0;
  save.lex.type = lex_none;
  return &save;
}