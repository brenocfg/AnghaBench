#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ hash_t ;
struct TYPE_2__ {int sp; } ;

/* Variables and functions */
 TYPE_1__* IHE ; 
 int MAX_WORDS ; 
 int* QOTW ; 
 char* QT ; 
 scalar_t__* QW ; 
 int Q_words ; 
 int /*<<< orphan*/  vkprintf (int,char*,scalar_t__,int) ; 

__attribute__((used)) static int add_query_word (hash_t word, char tag) {
  int i;
  for (i = 0; i < Q_words; i++) {
    if (QW[i] == word) {
      return i;
    }
  }
  if (i == MAX_WORDS) {
    return -1;
  }
  vkprintf (3, "add_query_word (%llx, %d)\n", word, (int) tag);
  QW[i] = word;
  QT[i] = tag;
  IHE[i].sp = -2;
  QOTW[i] = 1;
  return Q_words++;
}