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
struct stat {int /*<<< orphan*/  st_mode; } ;
struct jv_parser {int dummy; } ;
typedef  int /*<<< orphan*/  jv ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int ferror (int /*<<< orphan*/ *) ; 
 size_t fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int fstat (int,struct stat*) ; 
 int /*<<< orphan*/  jv_array () ; 
 int /*<<< orphan*/  jv_array_append (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_invalid_has_msg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_invalid_with_msg (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_parser_free (struct jv_parser*) ; 
 struct jv_parser* jv_parser_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_parser_next (struct jv_parser*) ; 
 int /*<<< orphan*/  jv_parser_set_buf (struct jv_parser*,char*,size_t,int) ; 
 int /*<<< orphan*/  jv_string (char*) ; 
 int /*<<< orphan*/  jv_string_append_buf (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  jv_string_fmt (char*,char const*,...) ; 
 scalar_t__ jvp_utf8_backtrack (char*,char*,int*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

jv jv_load_file(const char* filename, int raw) {
  struct stat sb;
  int fd = open(filename, O_RDONLY);
  if (fd == -1) {
    return jv_invalid_with_msg(jv_string_fmt("Could not open %s: %s",
                                             filename,
                                             strerror(errno)));
  }
  if (fstat(fd, &sb) == -1 || S_ISDIR(sb.st_mode)) {
    close(fd);
    return jv_invalid_with_msg(jv_string_fmt("Could not open %s: %s",
                                             filename,
                                             "It's a directory"));
  }
  FILE* file = fdopen(fd, "r");
  struct jv_parser* parser = NULL;
  jv data;
  if (!file) {
    close(fd);
    return jv_invalid_with_msg(jv_string_fmt("Could not open %s: %s",
                                             filename,
                                             strerror(errno)));
  }
  if (raw) {
    data = jv_string("");
  } else {
    data = jv_array();
    parser = jv_parser_new(0);
  }

  // To avoid mangling UTF-8 multi-byte sequences that cross the end of our read
  // buffer, we need to be able to read the remainder of a sequence and add that
  // before appending.
  const int max_utf8_len = 4;
  char buf[4096+max_utf8_len];
  while (!feof(file) && !ferror(file)) {
    size_t n = fread(buf, 1, sizeof(buf)-max_utf8_len, file);
    int len = 0;

    if (n == 0)
      continue;
    if (jvp_utf8_backtrack(buf+(n-1), buf, &len) && len > 0 &&
        !feof(file) && !ferror(file)) {
      n += fread(buf+n, 1, len, file);
    }

    if (raw) {
      data = jv_string_append_buf(data, buf, n);
    } else {
      jv_parser_set_buf(parser, buf, n, !feof(file));
      jv value;
      while (jv_is_valid((value = jv_parser_next(parser))))
        data = jv_array_append(data, value);
      if (jv_invalid_has_msg(jv_copy(value))) {
        jv_free(data);
        data = value;
        break;
      }
    }
  }
  if (!raw)
      jv_parser_free(parser);
  int badread = ferror(file);
  if (fclose(file) != 0 || badread) {
    jv_free(data);
    return jv_invalid_with_msg(jv_string_fmt("Error reading from %s",
                                             filename));
  }
  return data;
}