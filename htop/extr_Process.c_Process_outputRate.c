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
typedef  int /*<<< orphan*/  RichString ;

/* Variables and functions */
 int* CRT_colors ; 
 size_t LARGE_NUMBER ; 
 double ONE_K ; 
 size_t PROCESS ; 
 size_t PROCESS_MEGABYTES ; 
 size_t PROCESS_SHADOW ; 
 int /*<<< orphan*/  RichString_appendn (int /*<<< orphan*/ *,int,char*,int) ; 
 int snprintf (char*,int,char*,...) ; 

void Process_outputRate(RichString* str, char* buffer, int n, double rate, int coloring) {
   int largeNumberColor = CRT_colors[LARGE_NUMBER];
   int processMegabytesColor = CRT_colors[PROCESS_MEGABYTES];
   int processColor = CRT_colors[PROCESS];
   if (!coloring) {
      largeNumberColor = CRT_colors[PROCESS];
      processMegabytesColor = CRT_colors[PROCESS];
   }
   if (rate == -1) {
      int len = snprintf(buffer, n, "    no perm ");
      RichString_appendn(str, CRT_colors[PROCESS_SHADOW], buffer, len);
   } else if (rate < ONE_K) {
      int len = snprintf(buffer, n, "%7.2f B/s ", rate);
      RichString_appendn(str, processColor, buffer, len);
   } else if (rate < ONE_K * ONE_K) {
      int len = snprintf(buffer, n, "%7.2f K/s ", rate / ONE_K);
      RichString_appendn(str, processColor, buffer, len);
   } else if (rate < ONE_K * ONE_K * ONE_K) {
      int len = snprintf(buffer, n, "%7.2f M/s ", rate / ONE_K / ONE_K);
      RichString_appendn(str, processMegabytesColor, buffer, len);
   } else {
      int len = snprintf(buffer, n, "%7.2f G/s ", rate / ONE_K / ONE_K / ONE_K);
      RichString_appendn(str, largeNumberColor, buffer, len);
   }
}