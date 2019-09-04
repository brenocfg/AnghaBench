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
struct TYPE_5__ {TYPE_1__* metrics; } ;
struct TYPE_4__ {int /*<<< orphan*/ * member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ GTCStorageMetric ;
typedef  size_t GModule ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  DB_AGENTS ; 
 int /*<<< orphan*/  DB_BW ; 
 int /*<<< orphan*/  DB_CUMTS ; 
 int /*<<< orphan*/  DB_DATAMAP ; 
 int /*<<< orphan*/  DB_HITS ; 
 int /*<<< orphan*/  DB_KEYMAP ; 
 int /*<<< orphan*/  DB_MAXTS ; 
 int /*<<< orphan*/  DB_METADATA ; 
 int /*<<< orphan*/  DB_METHODS ; 
 int /*<<< orphan*/  DB_PROTOCOLS ; 
 int /*<<< orphan*/  DB_ROOT ; 
 int /*<<< orphan*/  DB_ROOTMAP ; 
 int /*<<< orphan*/  DB_UNIQMAP ; 
 int /*<<< orphan*/  DB_VISITORS ; 
 int /*<<< orphan*/  MTRC_AGENTS ; 
 int /*<<< orphan*/  MTRC_BW ; 
 int /*<<< orphan*/  MTRC_CUMTS ; 
 int /*<<< orphan*/  MTRC_DATAMAP ; 
 int /*<<< orphan*/  MTRC_HITS ; 
 int /*<<< orphan*/  MTRC_KEYMAP ; 
 int /*<<< orphan*/  MTRC_MAXTS ; 
 int /*<<< orphan*/  MTRC_METADATA ; 
 int /*<<< orphan*/  MTRC_METHODS ; 
 int /*<<< orphan*/  MTRC_PROTOCOLS ; 
 int /*<<< orphan*/  MTRC_ROOT ; 
 int /*<<< orphan*/  MTRC_ROOTMAP ; 
 int /*<<< orphan*/  MTRC_UNIQMAP ; 
 int /*<<< orphan*/  MTRC_VISITORS ; 
 TYPE_2__* tc_storage ; 

__attribute__((used)) static void
init_tables (GModule module)
{
  GTCStorageMetric mtrc;
  int n = 0, i;

  /* *INDENT-OFF* */
  GTCStorageMetric metrics[] = {
    {MTRC_KEYMAP    , DB_KEYMAP    , NULL, NULL} ,
    {MTRC_ROOTMAP   , DB_ROOTMAP   , NULL, NULL} ,
    {MTRC_DATAMAP   , DB_DATAMAP   , NULL, NULL} ,
    {MTRC_UNIQMAP   , DB_UNIQMAP   , NULL, NULL} ,
    {MTRC_ROOT      , DB_ROOT      , NULL, NULL} ,
    {MTRC_HITS      , DB_HITS      , NULL, NULL} ,
    {MTRC_VISITORS  , DB_VISITORS  , NULL, NULL} ,
    {MTRC_BW        , DB_BW        , NULL, NULL} ,
    {MTRC_CUMTS     , DB_CUMTS     , NULL, NULL} ,
    {MTRC_MAXTS     , DB_MAXTS     , NULL, NULL} ,
    {MTRC_METHODS   , DB_METHODS   , NULL, NULL} ,
    {MTRC_PROTOCOLS , DB_PROTOCOLS , NULL, NULL} ,
    {MTRC_AGENTS    , DB_AGENTS    , NULL, NULL} ,
    {MTRC_METADATA  , DB_METADATA  , NULL, NULL} ,
  };
  /* *INDENT-ON* */

  n = ARRAY_SIZE (metrics);
  for (i = 0; i < n; i++) {
    mtrc = metrics[i];
#ifdef TCB_MEMHASH
    mtrc.dbpath = get_dbname (mtrc.dbname, module);
    mtrc.store = tc_adb_create (mtrc.dbpath);
#endif
#ifdef TCB_BTREE
    /* allow for duplicate keys */
    if (mtrc.metric == MTRC_AGENTS) {
      mtrc.dbpath = tc_db_set_path (DB_AGENTS, module);
      mtrc.store = tc_bdb_create (mtrc.dbpath);
    } else {
      mtrc.dbpath = get_dbname (mtrc.dbname, module);
      mtrc.store = tc_adb_create (mtrc.dbpath);
    }
#endif
    tc_storage[module].metrics[i] = mtrc;
  }
}