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

/* Variables and functions */
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/ * stdout ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  utf8_printf (int /*<<< orphan*/ *,char*,char const*) ; 

__attribute__((used)) static FILE *output_file_open(const char *zFile, int bTextMode){
  FILE *f;
  if( strcmp(zFile,"stdout")==0 ){
    f = stdout;
  }else if( strcmp(zFile, "stderr")==0 ){
    f = stderr;
  }else if( strcmp(zFile, "off")==0 ){
    f = 0;
  }else{
    f = fopen(zFile, bTextMode ? "w" : "wb");
    if( f==0 ){
      utf8_printf(stderr, "Error: cannot open \"%s\"\n", zFile);
    }
  }
  return f;
}