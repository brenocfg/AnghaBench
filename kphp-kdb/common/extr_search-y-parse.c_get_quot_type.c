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
 int sqpt_double_quotation ; 
 int sqpt_no_quotation ; 
 int sqpt_single_quotation ; 

__attribute__((used)) static int get_quot_type (char ch) {
  switch (ch) {
    case '"': return sqpt_double_quotation; /* use stemmer */
    case '\'': return sqpt_single_quotation;
    default: return sqpt_no_quotation;
  }
}