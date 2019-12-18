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
typedef  scalar_t__ (* Object_Compare ) (void*,void*) ;
typedef  void Object ;

/* Variables and functions */
 int /*<<< orphan*/  comparisons ; 

__attribute__((used)) static void insertionSort(Object** array, int left, int right, Object_Compare compare) {
   for (int i = left+1; i <= right; i++) {
      void* t = array[i];
      int j = i - 1;
      while (j >= left) {
         comparisons++;
         if (compare(array[j], t) <= 0)
            break;
         array[j+1] = array[j];
         j--;
      }
      array[j+1] = t;
   }
}