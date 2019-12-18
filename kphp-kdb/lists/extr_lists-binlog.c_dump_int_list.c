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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 

void dump_int_list(FILE* f, int *s, int len) {
  int i;
  //fputc('{', f);  
  for(i=0;i<len;++i) {
    if (i > 0) fputc(':', f);
    //fprintf(f, "%d",(int) ((unsigned char) s[i]));
    fprintf(f, "%d", s[i]);
  } 
  //fputc('}', f);
}