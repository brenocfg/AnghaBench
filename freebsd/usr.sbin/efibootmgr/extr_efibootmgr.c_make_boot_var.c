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
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct entry {char* name; int /*<<< orphan*/  guid; } ;
typedef  char* efidp ;

/* Variables and functions */
 size_t BAD_LENGTH ; 
 int /*<<< orphan*/  COMMON_ATTRS ; 
 int /*<<< orphan*/  EFI_GLOBAL_GUID ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOAD_OPTION_ACTIVE ; 
 int /*<<< orphan*/  LOAD_OPTION_CATEGORY_BOOT ; 
 size_t MAX_DP_LEN ; 
 int MAX_LOADOPT_LEN ; 
 int /*<<< orphan*/  add_to_boot_order (char*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 size_t create_loadopt (char*,int,int /*<<< orphan*/ ,char*,size_t,char const*,char const*,scalar_t__) ; 
 int efi_set_variable (int /*<<< orphan*/ ,char*,char*,size_t,int /*<<< orphan*/ ) ; 
 size_t efidp_size (char*) ; 
 scalar_t__ efivar_unix_path_to_device_path (char const*,char**) ; 
 int /*<<< orphan*/  efivars ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* make_boot_var_name (int /*<<< orphan*/ ) ; 
 char* make_next_boot_var_name () ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  memset (struct entry*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int
make_boot_var(const char *label, const char *loader, const char *kernel, const char *env, bool dry_run,
    int bootnum, bool activate)
{
	struct entry *new_ent;
	uint32_t load_attrs = 0;
	uint8_t *load_opt_buf;
	size_t lopt_size, llen, klen;
	efidp dp, loaderdp, kerneldp;
	char *bootvar = NULL;
	int ret;

	assert(label != NULL);

	if (bootnum == -1)
		bootvar = make_next_boot_var_name();
	else
		bootvar = make_boot_var_name((uint16_t)bootnum);
	if (bootvar == NULL)
		err(1, "bootvar creation");
	if (loader == NULL)
		errx(1, "Must specify boot loader");
	if (efivar_unix_path_to_device_path(loader, &loaderdp) != 0)
		err(1, "Cannot translate unix loader path '%s' to UEFI", loader);
	if (kernel != NULL) {
		if (efivar_unix_path_to_device_path(kernel, &kerneldp) != 0)
			err(1, "Cannot translate unix kernel path '%s' to UEFI", kernel);
	} else {
		kerneldp = NULL;
	}
	llen = efidp_size(loaderdp);
	if (llen > MAX_DP_LEN)
		errx(1, "Loader path too long.");
	klen = efidp_size(kerneldp);
	if (klen > MAX_DP_LEN)
		errx(1, "Kernel path too long.");
	dp = malloc(llen + klen);
	if (dp == NULL)
		errx(1, "Can't allocate memory for new device paths");
	memcpy(dp, loaderdp, llen);
	if (kerneldp != NULL)
		memcpy((char *)dp + llen, kerneldp, klen);

	/* don't make the new bootvar active by default, use the -a option later */
	load_attrs = LOAD_OPTION_CATEGORY_BOOT;
	if (activate)
		load_attrs |= LOAD_OPTION_ACTIVE;
	load_opt_buf = malloc(MAX_LOADOPT_LEN);
	if (load_opt_buf == NULL)
		err(1, "malloc");

	lopt_size = create_loadopt(load_opt_buf, MAX_LOADOPT_LEN, load_attrs,
	    dp, llen + klen, label, env, env ? strlen(env) + 1 : 0);
	if (lopt_size == BAD_LENGTH)
		errx(1, "Can't create loadopt");

	ret = 0;
	if (!dry_run) {
		ret = efi_set_variable(EFI_GLOBAL_GUID, bootvar,
		    (uint8_t*)load_opt_buf, lopt_size, COMMON_ATTRS);
	}

	if (ret)
		err(1, "efi_set_variable");

	if (!dry_run)
		add_to_boot_order(bootvar); /* first, still not active */
	new_ent = malloc(sizeof(struct entry));
	if (new_ent == NULL)
		err(1, "malloc");
	memset(new_ent, 0, sizeof(struct entry));
	new_ent->name = bootvar;
	new_ent->guid = EFI_GLOBAL_GUID;
	LIST_INSERT_HEAD(&efivars, new_ent, entries);
	free(load_opt_buf);
	free(dp);

	return 0;
}