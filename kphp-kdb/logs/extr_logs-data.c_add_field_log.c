#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct lev_logs_add_field {int /*<<< orphan*/  text; } ;
struct TYPE_5__ {int field_i; TYPE_1__* fields; int /*<<< orphan*/ * name; } ;
struct TYPE_4__ {int type; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int MAX_TYPE ; 
 int /*<<< orphan*/  add_field (TYPE_2__*,char*,int) ; 
 char* buff ; 
 char* dl_pstr (char*,...) ; 
 int /*<<< orphan*/  dl_strhash (char*) ; 
 int get_type (char*) ; 
 int /*<<< orphan*/  is_name (char*) ; 
 int* map_ll_int_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_type_id ; 
 int /*<<< orphan*/  sscanf (char*,char*,int*,int*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int t_string ; 
 int* ttt_size ; 
 TYPE_2__* types ; 

char *add_field_log (struct lev_logs_add_field *E) {
  strcpy (buff, E->text);
  int i = 0;

  while (buff[i] != ',' && buff[i]) {
    i++;
  }

  if (buff[i] != ',') {
    return dl_pstr ("Wrong number of parameters.");
  }

  buff[i] = 0;

  int type_id;

  if (buff[0] >= '1' && buff[0] <= '9') {
    int len;
    sscanf (buff, "%d%n", &type_id, &len);
    if (len != i) {
      return dl_pstr ("Not a valid name [%s] for type_id.", buff);
    }

    if (!(1 <= type_id && type_id < MAX_TYPE)) {
      return dl_pstr ("Type_id [%d] not in range [1;%d].", type_id, MAX_TYPE - 1);
    }

    if (types[type_id].name == NULL) {
      return dl_pstr ("Type [%d] doesn't exist. You need to create it first.", type_id);
    }
  } else {
    if (!is_name (buff)) {
      return dl_pstr ("Not a valid name [%s] for type_id.", buff);
    }

    int *ptmp = map_ll_int_get (&map_type_id, dl_strhash (buff));
    if (ptmp == NULL) {
      return dl_pstr ("There is no type named [%s].", buff);
    }

    type_id = *ptmp;
  }

  int j = i + 1;
  while (buff[j] != ':' && buff[j]) {
    j++;
  }

  if (buff[j] != ':') {
    return dl_pstr ("Not enough parameters in field description.");
  }
  buff[j] = 0;

  int type = get_type (buff + j + 1);
  if (type == -1) {
    return dl_pstr ("Wrond type of new field [%s].", buff + j + 1);
  }
  char *name = buff + i + 1;

  if (!is_name (name)) {
    return dl_pstr ("Not a valid name [%s] for field_name.", name);
  }

  if (type < t_string) {
    int size = ttt_size[type];
    for (i = 0; i < types[type_id].field_i; i++) {
      if (types[type_id].fields[i].type < t_string) {
        size += ttt_size[types[type_id].fields[i].type];
      }
    }

    if (size >= 248) {
      return dl_pstr ("Max size (248) of nunber fields of type [%s] exceeded. Contact soft developers for help.", types[type_id].name);
    }
  }

  if (types[type_id].field_i >= 64) {
    return dl_pstr ("Max number (64) of fields for type [%s] already created. Contact soft developers for help.", buff);
  }

  for (i = 0; i < types[type_id].field_i; i++) {
    if (strcmp (types[type_id].fields[i].name, name) == 0) {
      return dl_pstr ("Field with name [%s] already exists in type [%s].", name, buff);
    }
  }

  add_field (&types[type_id], name, type);
  return "OK";
}