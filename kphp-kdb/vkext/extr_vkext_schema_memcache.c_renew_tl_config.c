#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tl_type {int extra; int constructors_num; int /*<<< orphan*/ * constructors; } ;
struct tl_combinator {int dummy; } ;
struct TYPE_4__ {int tn; int cn; int fn; struct tl_combinator** fns; struct tl_type** tps; } ;
struct TYPE_3__ {scalar_t__ rptr; scalar_t__ wptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_PFREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADD_PMALLOC (int) ; 
 int TLS_COMBINATOR ; 
 int TLS_TYPE ; 
 long long config_crc64 ; 
 long long crc64_partial (scalar_t__,int,long long) ; 
 TYPE_2__* cur_config ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ gen_constructor_fetch (int /*<<< orphan*/ ,void**,int) ; 
 scalar_t__ gen_constructor_store (int /*<<< orphan*/ ,void**,int) ; 
 scalar_t__ gen_function_fetch (void**,int) ; 
 scalar_t__ gen_function_store (struct tl_combinator*,void**,int) ; 
 int get_schema_version (int) ; 
 TYPE_1__* inbuf ; 
 struct tl_combinator* read_combinators (int) ; 
 struct tl_type* read_types () ; 
 int schema_version ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlen (scalar_t__) ; 
 int /*<<< orphan*/  tl_config_alloc () ; 
 int /*<<< orphan*/  tl_config_back () ; 
 int tl_config_date ; 
 scalar_t__ tl_config_name ; 
 int tl_config_version ; 
 int /*<<< orphan*/  tl_parse_end () ; 
 scalar_t__ tl_parse_error () ; 
 int /*<<< orphan*/  tl_parse_init () ; 
 int tl_parse_int () ; 
 int verbosity ; 
 void* zzmalloc0 (int) ; 
 int /*<<< orphan*/  zzstrfree (scalar_t__) ; 

int renew_tl_config (void) {
  if (verbosity >= 2) {
    fprintf (stderr, "Starting config renew\n");
  }
  tl_parse_init ();
  int x = tl_parse_int ();
  if (verbosity >= 2) {
    fprintf (stderr, "Schema 0x%08x\n", x);
  }
  schema_version = get_schema_version (x);
  if (verbosity >= 2) {
    fprintf (stderr, "Schema version %d\n", schema_version);
  }
  if (schema_version <= 0 || tl_parse_error ()) {
    return -1;
  }

  int new_tl_config_version = tl_parse_int ();
  int new_tl_config_date = tl_parse_int ();

  if (tl_parse_error ()) {
    return -1;
  }

  long long new_crc64 = crc64_partial (inbuf->rptr, ((char *)inbuf->wptr) - (char *)inbuf->rptr,-1ll);
  if (new_tl_config_version < tl_config_version || (new_tl_config_version == tl_config_version && new_tl_config_date < tl_config_date) || config_crc64 == new_crc64) {
    return 0;
  }

  tl_config_alloc ();
//  int x;

//  struct tl_type *tps [10000];
  int tn = 0;
//  struct tl_combinator *fns [10000];
  int fn = 0;
  int cn;
  int i;

  tn = tl_parse_int ();
  if (tn < 0 || tn > 10000 || tl_parse_error ()) {
    tl_config_back ();
    return -1;
  }
  
  cur_config->tps = zzmalloc0 (sizeof (void *) * tn);
  cur_config->tn = tn;
  ADD_PMALLOC (tn * sizeof (void *));
  struct tl_type **tps = cur_config->tps;
  if (verbosity >= 2) {
    fprintf (stderr, "Found %d types\n", tn);
  }

  for (i = 0; i < tn; i++) {
    if (tl_parse_int () != TLS_TYPE) { 
      tl_config_back ();
      return -1; 
    }
    tps[i] = read_types ();
    if (!tps[i]) { 
      tl_config_back ();
      return -1; 
    }
  }

  cn = tl_parse_int ();  
  if (cn < 0 || tl_parse_error ()) {
    tl_config_back ();
    return -1;
  }
  cur_config->cn = cn;

  if (verbosity >= 2) {
    fprintf (stderr, "Found %d constructors\n", cn);
  }

  for (i = 0; i < cn; i++) {
    if (tl_parse_int () != TLS_COMBINATOR) { 
      tl_config_back ();
      return -1; 
    }
    if (!read_combinators (2)) {
      tl_config_back ();
      return -1;
    }
  }
  fn = tl_parse_int ();
  if (fn < 0 || fn > 10000 || tl_parse_error ()) {
    tl_config_back ();
    return -1;
  }
  cur_config->fn = fn;
  cur_config->fns = zzmalloc0 (sizeof (void *) * fn);
  ADD_PMALLOC (fn * sizeof (void *));
  struct tl_combinator **fns = cur_config->fns;
  
  if (verbosity >= 2) {
    fprintf (stderr, "Found %d functions\n", fn);
  }

  for (i = 0; i < fn; i++) {
    if (tl_parse_int () != TLS_COMBINATOR) { 
      tl_config_back ();
      return -1; 
    }
    fns[i] = read_combinators (3);
    if (!fns[i]) { 
      tl_config_back ();
      return -1; 
    }
  }
  tl_parse_end ();
  if (tl_parse_error ()) {
    tl_config_back ();
    return -1;
  }
  static void *IP[10000];
  if (gen_function_fetch (IP, 100) < 0) {
    return -2;
  }
  for (i = 0; i < tn; i++) {
    if (tps[i]->extra < tps[i]->constructors_num) {
      tl_config_back ();
      return -1;
    }
  }
  int j;
  for (i = 0; i < tn; i++) {
    for (j = 0; j < tps[i]->constructors_num; j ++) {
      if (gen_constructor_store (tps[i]->constructors[j], IP, 10000) < 0) {
        return -2;
      }
      if (gen_constructor_fetch (tps[i]->constructors[j], IP, 10000) < 0) {
        return -2;
      }
    }
  }  
  for (i = 0; i < fn; i++) {
    if (gen_function_store (fns[i], IP, 10000) < 0) {
      return -2;
    }
  }
  if (tl_config_name) {
    ADD_PFREE (strlen (tl_config_name));
    zzstrfree (tl_config_name);
  }
  tl_config_name = 0;
  config_crc64 = new_crc64;
  tl_config_version = new_tl_config_version ;
  tl_config_date = new_tl_config_date;
  return 1;
}