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

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 char* po_olddir ; 
 int /*<<< orphan*/  replace_char (char*,char,char) ; 
 int snprintf (char*,int,char*,char*,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char const* const) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void compute_temporary_filename (int transaction_id, int *transaction_file_no, const char *const name, char out[PATH_MAX]) {
  const int MAX_PREFIX_LENGTH = 64;
  char tmp_name[PATH_MAX];
  strcpy (tmp_name, name);
  replace_char (tmp_name, '/', '$');
  const char *p = tmp_name, *q = p + strlen (p);
  if (q - p >= MAX_PREFIX_LENGTH) { p = q - MAX_PREFIX_LENGTH; }
  assert (snprintf (out, PATH_MAX, "%s/%s.%d.%d", po_olddir, p, transaction_id, (*transaction_file_no)++) < PATH_MAX);
}