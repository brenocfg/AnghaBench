#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct entry {char* principal; char* key; char* created; char* modified; char* valid_start; char* valid_end; char* pw_end; char* max_life; char* max_renew; char* flags; char* generation; char* extensions; } ;
typedef  int /*<<< orphan*/  s ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_13__ {int /*<<< orphan*/  extensions; int /*<<< orphan*/  generation; int /*<<< orphan*/  flags; int /*<<< orphan*/  max_renew; int /*<<< orphan*/  max_life; int /*<<< orphan*/  pw_end; int /*<<< orphan*/  valid_end; int /*<<< orphan*/  valid_start; int /*<<< orphan*/  modified_by; int /*<<< orphan*/  created_by; int /*<<< orphan*/  principal; } ;
struct TYPE_11__ {TYPE_7__ entry; } ;
typedef  TYPE_1__ hdb_entry_ex ;
typedef  int /*<<< orphan*/  ent ;
struct TYPE_12__ {scalar_t__ (* hdb_open ) (int /*<<< orphan*/ ,TYPE_2__*,int,int) ;scalar_t__ (* hdb_store ) (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ;int /*<<< orphan*/  (* hdb_close ) (int /*<<< orphan*/ ,TYPE_2__*) ;} ;
typedef  TYPE_2__ HDB ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  HDB_F_REPLACE ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 TYPE_2__* _kadm5_s_get_db (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,int,char const*,...) ; 
 int /*<<< orphan*/  hdb_free_entry (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ isspace (unsigned char) ; 
 scalar_t__ kadm5_log_truncate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kadm_handle ; 
 int /*<<< orphan*/  krb5_free_error_message (int /*<<< orphan*/ ,char const*) ; 
 char* krb5_get_error_message (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ krb5_parse_name (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,scalar_t__,char*,...) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int parse_event (int /*<<< orphan*/ *,char*) ; 
 int parse_event_alloc (int /*<<< orphan*/ *,char*) ; 
 int parse_extensions (char*,int /*<<< orphan*/ *) ; 
 int parse_generation (char*,int /*<<< orphan*/ *) ; 
 int parse_hdbflags2int (int /*<<< orphan*/ *,char*) ; 
 int parse_integer_alloc (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ parse_keys (TYPE_7__*,char*) ; 
 int parse_time_string_alloc (int /*<<< orphan*/ *,char*) ; 
 char* skip_next (char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_2__*,int,int) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int
doit(const char *filename, int mergep)
{
    krb5_error_code ret;
    FILE *f;
    char s[8192]; /* XXX should fix this properly */
    char *p;
    int line;
    int flags = O_RDWR;
    struct entry e;
    hdb_entry_ex ent;
    HDB *db = _kadm5_s_get_db(kadm_handle);

    f = fopen(filename, "r");
    if(f == NULL){
	krb5_warn(context, errno, "fopen(%s)", filename);
	return 1;
    }
    ret = kadm5_log_truncate (kadm_handle);
    if (ret) {
	fclose (f);
	krb5_warn(context, ret, "kadm5_log_truncate");
	return 1;
    }

    if(!mergep)
	flags |= O_CREAT | O_TRUNC;
    ret = db->hdb_open(context, db, flags, 0600);
    if(ret){
	krb5_warn(context, ret, "hdb_open");
	fclose(f);
	return 1;
    }
    line = 0;
    ret = 0;
    while(fgets(s, sizeof(s), f) != NULL) {
	line++;

	p = s;
	while (isspace((unsigned char)*p))
	    p++;

	e.principal = p;
	for(p = s; *p; p++){
	    if(*p == '\\')
		p++;
	    else if(isspace((unsigned char)*p)) {
		*p = 0;
		break;
	    }
	}
	p = skip_next(p);

	e.key = p;
	p = skip_next(p);

	e.created = p;
	p = skip_next(p);

	e.modified = p;
	p = skip_next(p);

	e.valid_start = p;
	p = skip_next(p);

	e.valid_end = p;
	p = skip_next(p);

	e.pw_end = p;
	p = skip_next(p);

	e.max_life = p;
	p = skip_next(p);

	e.max_renew = p;
	p = skip_next(p);

	e.flags = p;
	p = skip_next(p);

	e.generation = p;
	p = skip_next(p);

	e.extensions = p;
	skip_next(p);

	memset(&ent, 0, sizeof(ent));
	ret = krb5_parse_name(context, e.principal, &ent.entry.principal);
	if(ret) {
	    const char *msg = krb5_get_error_message(context, ret);
	    fprintf(stderr, "%s:%d:%s (%s)\n",
		    filename, line, msg, e.principal);
	    krb5_free_error_message(context, msg);
	    continue;
	}

	if (parse_keys(&ent.entry, e.key)) {
	    fprintf (stderr, "%s:%d:error parsing keys (%s)\n",
		     filename, line, e.key);
	    hdb_free_entry (context, &ent);
	    continue;
	}

	if (parse_event(&ent.entry.created_by, e.created) == -1) {
	    fprintf (stderr, "%s:%d:error parsing created event (%s)\n",
		     filename, line, e.created);
	    hdb_free_entry (context, &ent);
	    continue;
	}
	if (parse_event_alloc (&ent.entry.modified_by, e.modified) == -1) {
	    fprintf (stderr, "%s:%d:error parsing event (%s)\n",
		     filename, line, e.modified);
	    hdb_free_entry (context, &ent);
	    continue;
	}
	if (parse_time_string_alloc (&ent.entry.valid_start, e.valid_start) == -1) {
	    fprintf (stderr, "%s:%d:error parsing time (%s)\n",
		     filename, line, e.valid_start);
	    hdb_free_entry (context, &ent);
	    continue;
	}
	if (parse_time_string_alloc (&ent.entry.valid_end,   e.valid_end) == -1) {
	    fprintf (stderr, "%s:%d:error parsing time (%s)\n",
		     filename, line, e.valid_end);
	    hdb_free_entry (context, &ent);
	    continue;
	}
	if (parse_time_string_alloc (&ent.entry.pw_end,      e.pw_end) == -1) {
	    fprintf (stderr, "%s:%d:error parsing time (%s)\n",
		     filename, line, e.pw_end);
	    hdb_free_entry (context, &ent);
	    continue;
	}

	if (parse_integer_alloc (&ent.entry.max_life,  e.max_life) == -1) {
	    fprintf (stderr, "%s:%d:error parsing lifetime (%s)\n",
		     filename, line, e.max_life);
	    hdb_free_entry (context, &ent);
	    continue;

	}
	if (parse_integer_alloc (&ent.entry.max_renew, e.max_renew) == -1) {
	    fprintf (stderr, "%s:%d:error parsing lifetime (%s)\n",
		     filename, line, e.max_renew);
	    hdb_free_entry (context, &ent);
	    continue;
	}

	if (parse_hdbflags2int (&ent.entry.flags, e.flags) != 1) {
	    fprintf (stderr, "%s:%d:error parsing flags (%s)\n",
		     filename, line, e.flags);
	    hdb_free_entry (context, &ent);
	    continue;
	}

	if(parse_generation(e.generation, &ent.entry.generation) == -1) {
	    fprintf (stderr, "%s:%d:error parsing generation (%s)\n",
		     filename, line, e.generation);
	    hdb_free_entry (context, &ent);
	    continue;
	}

	if(parse_extensions(e.extensions, &ent.entry.extensions) == -1) {
	    fprintf (stderr, "%s:%d:error parsing extension (%s)\n",
		     filename, line, e.extensions);
	    hdb_free_entry (context, &ent);
	    continue;
	}

	ret = db->hdb_store(context, db, HDB_F_REPLACE, &ent);
	hdb_free_entry (context, &ent);
	if (ret) {
	    krb5_warn(context, ret, "db_store");
	    break;
	}
    }
    db->hdb_close(context, db);
    fclose(f);
    return ret != 0;
}