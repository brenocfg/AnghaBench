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
typedef  int /*<<< orphan*/  Command ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND_COMPRESS ; 
 int /*<<< orphan*/  COMMAND_DECOMPRESS ; 
 char* FileName (char const*) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,size_t) ; 

__attribute__((used)) static Command ParseAlias(const char* name) {
  /* TODO: cast name to lower case? */
  const char* unbrotli = "unbrotli";
  size_t unbrotli_len = strlen(unbrotli);
  name = FileName(name);
  /* Partial comparison. On Windows there could be ".exe" suffix. */
  if (strncmp(name, unbrotli, unbrotli_len) == 0) {
    char terminator = name[unbrotli_len];
    if (terminator == 0 || terminator == '.') return COMMAND_DECOMPRESS;
  }
  return COMMAND_COMPRESS;
}