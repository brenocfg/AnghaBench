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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fputc (char const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void python_dump (const char *s, const char *e) {
  fprintf (stderr, "packet = \"");
  while (s != e) {
    if (*s >= 32 && *s < 128 && *s != '"' && *s != '\'' && *s != '\\') {
      fputc (*s, stderr);
    } else {
      fprintf (stderr, "\\x%02x", (int) ((unsigned char) *s));
    }
    s++;
  }
  fprintf (stderr, "\"\n");
}