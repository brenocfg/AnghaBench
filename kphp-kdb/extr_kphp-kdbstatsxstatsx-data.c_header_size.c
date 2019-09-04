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
struct index_header_v2 {int dummy; } ;
struct index_header_v1 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int index_version ; 

int header_size (void) {
  if (index_version == 1 || index_version == 0) {
    return sizeof (struct index_header_v1);
  } else if (index_version == 2) {
    return sizeof (struct index_header_v2);
  } else if (index_version == 3) {
    return sizeof (struct index_header_v2);
  } else if (index_version == 4) {
    return sizeof (struct index_header_v2);
  } else {
    assert (0);
    return 0;
  }
}