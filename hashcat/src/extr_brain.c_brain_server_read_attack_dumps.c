#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct dirent {char* d_name; } ;
struct TYPE_3__ {size_t attack_cnt; int /*<<< orphan*/ * attack_buf; } ;
typedef  TYPE_1__ brain_server_dbs_t ;
typedef  int /*<<< orphan*/  brain_server_db_attack_t ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  brain_logging (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brain_server_db_attack_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 
 int brain_server_read_attack_dump (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  byte_swap_32 (int /*<<< orphan*/ ) ; 
 int chdir (char const*) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  hex_to_u32 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 

bool brain_server_read_attack_dumps (brain_server_dbs_t *brain_server_dbs, const char *path)
{
  brain_server_dbs->attack_cnt = 0;

  if (chdir (path) == -1)
  {
    brain_logging (stderr, 0, "%s: %s\n", path, strerror (errno));

    return false;
  }

  DIR *dirp = opendir (path);

  if (dirp == NULL)
  {
    brain_logging (stderr, 0, "%s: %s\n", path, strerror (errno));

    return false;
  }

  struct dirent *entry = NULL;

  while ((entry = readdir (dirp)) != NULL)
  {
    char *file = entry->d_name;

    const size_t len = strlen (file);

    if (len != 19) continue;

    if (file[ 0] != 'b') continue;
    if (file[ 1] != 'r') continue;
    if (file[ 2] != 'a') continue;
    if (file[ 3] != 'i') continue;
    if (file[ 4] != 'n') continue;
    if (file[ 5] != '.') continue;

    if (file[14] != '.') continue;
    if (file[15] != 'a') continue;
    if (file[16] != 'd') continue;
    if (file[17] != 'm') continue;
    if (file[18] != 'p') continue;

    const u32 brain_attack = byte_swap_32 (hex_to_u32 ((const u8 *) file + 6));

    brain_server_db_attack_t *brain_server_db_attack = &brain_server_dbs->attack_buf[brain_server_dbs->attack_cnt];

    brain_server_db_attack_init (brain_server_db_attack, brain_attack);

    if (brain_server_read_attack_dump (brain_server_db_attack, file) == false) continue;

    brain_server_dbs->attack_cnt++;
  }

  closedir (dirp);

  return true;
}