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
struct item {int key_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 struct item* preload_key (int,int const*,int) ; 

struct item *get (int key_len, const int *key) {
  assert (key_len >= 0 && key_len <= 255);
  struct item *I = preload_key (key_len, key, 1);
  if (I->key_len == -2) {
    return 0;
  }
  return I;  
}