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
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 char* fgets (char*,int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strrchr (char*,char) ; 
 char* xMalloc (int const) ; 
 char* xRealloc (char*,int) ; 

char* String_readLine(FILE* fd) {
   const int step = 1024;
   int bufSize = step;
   char* buffer = xMalloc(step + 1);
   char* at = buffer;
   for (;;) {
      char* ok = fgets(at, step + 1, fd);
      if (!ok) {
         free(buffer);
         return NULL;
      }
      char* newLine = strrchr(at, '\n');
      if (newLine) {
         *newLine = '\0';
         return buffer;
      } else {
         if (feof(fd)) {
            return buffer;
         }
      }
      bufSize += step;
      buffer = xRealloc(buffer, bufSize + 1);
      at = buffer + bufSize - step;
   }
}