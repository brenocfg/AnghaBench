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
struct TYPE_2__ {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int MAX_TYPE ; 
 int /*<<< orphan*/  dl_strhash (char*) ; 
 int /*<<< orphan*/  is_name (char*) ; 
 int* map_ll_int_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_type_id ; 
 int /*<<< orphan*/  sscanf (char*,char*,int*,int*) ; 
 int strlen (char*) ; 
 TYPE_1__* types ; 

int get_type_id (char *s) {
  int type_id;
  int sn = strlen (s);
  if (s[0] >= '1' && s[0] <= '9') {
    int len;
    sscanf (s, "%d%n", &type_id, &len);
    if (len != sn) {
      return 0;
    }

    if (!(1 <= type_id && type_id < MAX_TYPE)) {
      return 0;
    }

    if (types[type_id].name == NULL) {
      return 0;
    }
  } else {
    if (!is_name (s)) {
      return 0;
    }

    int *ptmp = map_ll_int_get (&map_type_id, dl_strhash (s));
    if (ptmp == NULL) {
      return 0;
    }

    type_id = *ptmp;
  }
  return type_id;
}