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
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  BROTLI_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BROTLI_FALSE ; 
 int /*<<< orphan*/  BROTLI_TRUE ; 
 int /*<<< orphan*/  MAKE_BINARY (int /*<<< orphan*/ ) ; 
 char* PrintablePath (char const*) ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * fdopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BROTLI_BOOL OpenInputFile(const char* input_path, FILE** f) {
  *f = NULL;
  if (!input_path) {
    *f = fdopen(MAKE_BINARY(STDIN_FILENO), "rb");
    return BROTLI_TRUE;
  }
  *f = fopen(input_path, "rb");
  if (!*f) {
    fprintf(stderr, "failed to open input file [%s]: %s\n",
            PrintablePath(input_path), strerror(errno));
    return BROTLI_FALSE;
  }
  return BROTLI_TRUE;
}