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
struct TYPE_3__ {struct _gss_mech_switch* elements; } ;
struct _gss_mech_switch {char const* gm_name_prefix; TYPE_1__ gm_mech_oid; void* gm_so; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  scalar_t__ OM_uint32 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  OPTSYM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTLD_LOCAL ; 
 scalar_t__ SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct _gss_mech_switch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _PATH_GSS_MECH ; 
 int /*<<< orphan*/  _gss_mech_oids ; 
 int /*<<< orphan*/  _gss_mechs ; 
 scalar_t__ _gss_string_to_oid (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  accept_sec_context ; 
 int /*<<< orphan*/  acquire_cred ; 
 int /*<<< orphan*/  add_cred ; 
 int /*<<< orphan*/  canonicalize_name ; 
 int /*<<< orphan*/  compare_name ; 
 int /*<<< orphan*/  context_time ; 
 int /*<<< orphan*/  delete_sec_context ; 
 int /*<<< orphan*/  display_name ; 
 int /*<<< orphan*/  display_status ; 
 int /*<<< orphan*/  dlclose (void*) ; 
 char* dlerror () ; 
 void* dlopen (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ dlsym (void*,char*) ; 
 int /*<<< orphan*/  duplicate_name ; 
 int /*<<< orphan*/  export_name ; 
 int /*<<< orphan*/  export_sec_context ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (struct _gss_mech_switch*) ; 
 int /*<<< orphan*/  get_mic ; 
 int /*<<< orphan*/  gm_link ; 
 scalar_t__ gss_add_oid_set_member (scalar_t__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ gss_create_empty_oid_set (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  import_name ; 
 int /*<<< orphan*/  import_sec_context ; 
 int /*<<< orphan*/  indicate_mechs ; 
 int /*<<< orphan*/  init_sec_context ; 
 int /*<<< orphan*/  inquire_context ; 
 int /*<<< orphan*/  inquire_cred ; 
 int /*<<< orphan*/  inquire_cred_by_mech ; 
 int /*<<< orphan*/  inquire_cred_by_oid ; 
 int /*<<< orphan*/  inquire_mechs_for_name ; 
 int /*<<< orphan*/  inquire_names_for_mech ; 
 int /*<<< orphan*/  inquire_sec_context_by_oid ; 
 scalar_t__ isspace (char) ; 
 struct _gss_mech_switch* malloc (int) ; 
 int /*<<< orphan*/  perror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pname_to_uid ; 
 int /*<<< orphan*/  process_context_token ; 
 int /*<<< orphan*/  pseudo_random ; 
 int /*<<< orphan*/  release_cred ; 
 int /*<<< orphan*/  release_name ; 
 int /*<<< orphan*/  set_cred_option ; 
 int /*<<< orphan*/  set_sec_context_option ; 
 int /*<<< orphan*/  stderr ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  unwrap ; 
 int /*<<< orphan*/  verify_mic ; 
 int /*<<< orphan*/  wrap ; 
 int /*<<< orphan*/  wrap_size_limit ; 

void
_gss_load_mech(void)
{
	OM_uint32	major_status, minor_status;
	FILE		*fp;
	char		buf[256];
	char		*p;
	char		*name, *oid, *lib, *kobj;
	struct _gss_mech_switch *m;
	int		count;
	void		*so;
	const char	*(*prefix_fn)(void);

	if (SLIST_FIRST(&_gss_mechs))
		return;

	major_status = gss_create_empty_oid_set(&minor_status,
	    &_gss_mech_oids);
	if (major_status)
		return;

	fp = fopen(_PATH_GSS_MECH, "r");
	if (!fp) {
		perror(_PATH_GSS_MECH);
		return;
	}

	count = 0;
	while (fgets(buf, sizeof(buf), fp)) {
		if (*buf == '#')
			continue;
		p = buf;
		name = strsep(&p, "\t\n ");
		if (p) while (isspace(*p)) p++;
		oid = strsep(&p, "\t\n ");
		if (p) while (isspace(*p)) p++;
		lib = strsep(&p, "\t\n ");
		if (p) while (isspace(*p)) p++;
		kobj = strsep(&p, "\t\n ");
		if (!name || !oid || !lib || !kobj)
			continue;

		so = dlopen(lib, RTLD_LOCAL);
		if (!so) {
			fprintf(stderr, "dlopen: %s\n", dlerror());
			continue;
		}

		m = malloc(sizeof(struct _gss_mech_switch));
		if (!m)
			break;
		m->gm_so = so;
		if (_gss_string_to_oid(oid, &m->gm_mech_oid)) {
			free(m);
			continue;
		}
		
		prefix_fn = (const char *(*)(void))
			dlsym(so, "_gss_name_prefix");
		if (prefix_fn)
			m->gm_name_prefix = prefix_fn();
		else
			m->gm_name_prefix = "gss";

		major_status = gss_add_oid_set_member(&minor_status,
		    &m->gm_mech_oid, &_gss_mech_oids);
		if (major_status) {
			free(m->gm_mech_oid.elements);
			free(m);
			continue;
		}

		SYM(acquire_cred);
		SYM(release_cred);
		SYM(init_sec_context);
		SYM(accept_sec_context);
		SYM(process_context_token);
		SYM(delete_sec_context);
		SYM(context_time);
		SYM(get_mic);
		SYM(verify_mic);
		SYM(wrap);
		SYM(unwrap);
		SYM(display_status);
		OPTSYM(indicate_mechs);
		SYM(compare_name);
		SYM(display_name);
		SYM(import_name);
		SYM(export_name);
		SYM(release_name);
		SYM(inquire_cred);
		SYM(inquire_context);
		SYM(wrap_size_limit);
		SYM(add_cred);
		SYM(inquire_cred_by_mech);
		SYM(export_sec_context);
		SYM(import_sec_context);
		SYM(inquire_names_for_mech);
		SYM(inquire_mechs_for_name);
		SYM(canonicalize_name);
		SYM(duplicate_name);
		OPTSYM(inquire_sec_context_by_oid);
		OPTSYM(inquire_cred_by_oid);
		OPTSYM(set_sec_context_option);
		OPTSYM(set_cred_option);
		OPTSYM(pseudo_random);
		OPTSYM(pname_to_uid);

		SLIST_INSERT_HEAD(&_gss_mechs, m, gm_link);
		count++;
		continue;

	bad:
		free(m->gm_mech_oid.elements);
		free(m);
		dlclose(so);
		continue;
	}
	fclose(fp);
}