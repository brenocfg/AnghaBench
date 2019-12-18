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
 int /*<<< orphan*/  Argv0 ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  raw_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  utf8_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zOptions ; 

__attribute__((used)) static void usage(int showDetail){
  utf8_printf(stderr,
      "Usage: %s [OPTIONS] FILENAME [SQL]\n"
      "FILENAME is the name of an SQLite database. A new database is created\n"
      "if the file does not previously exist.\n", Argv0);
  if( showDetail ){
    utf8_printf(stderr, "OPTIONS include:\n%s", zOptions);
  }else{
    raw_printf(stderr, "Use the -help option for additional information\n");
  }
  exit(1);
}