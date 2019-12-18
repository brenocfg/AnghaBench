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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int ConfigLevel ; 
 int MAXLINE ; 
 int MAXMAPACTIONS ; 
 int MAXMAPSTACK ; 
 int /*<<< orphan*/  ST_FIND ; 
 int /*<<< orphan*/  ST_MAP ; 
 int /*<<< orphan*/  makemapentry (char*) ; 
 int /*<<< orphan*/  sm_strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  sm_strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/ * stab (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int switch_map_find (char*,char**,short*) ; 

void
inithostmaps()
{
	register int i;
	int nmaps;
	char *maptype[MAXMAPSTACK];
	short mapreturn[MAXMAPACTIONS];
	char buf[MAXLINE];

	/*
	**  Make sure we have a host map.
	*/

	if (stab("host", ST_MAP, ST_FIND) == NULL)
	{
		/* user didn't initialize: set up host map */
		(void) sm_strlcpy(buf, "host host", sizeof(buf));
#if NAMED_BIND
		if (ConfigLevel >= 2)
			(void) sm_strlcat(buf, " -a. -D", sizeof(buf));
#endif /* NAMED_BIND */
		(void) makemapentry(buf);
	}

	/*
	**  Set up default aliases maps
	*/

	nmaps = switch_map_find("aliases", maptype, mapreturn);
	for (i = 0; i < nmaps; i++)
	{
		if (strcmp(maptype[i], "files") == 0 &&
		    stab("aliases.files", ST_MAP, ST_FIND) == NULL)
		{
			(void) sm_strlcpy(buf, "aliases.files null",
					  sizeof(buf));
			(void) makemapentry(buf);
		}
#if NISPLUS
		else if (strcmp(maptype[i], "nisplus") == 0 &&
			 stab("aliases.nisplus", ST_MAP, ST_FIND) == NULL)
		{
			(void) sm_strlcpy(buf, "aliases.nisplus nisplus -kalias -vexpansion mail_aliases.org_dir",
				sizeof(buf));
			(void) makemapentry(buf);
		}
#endif /* NISPLUS */
#if NIS
		else if (strcmp(maptype[i], "nis") == 0 &&
			 stab("aliases.nis", ST_MAP, ST_FIND) == NULL)
		{
			(void) sm_strlcpy(buf, "aliases.nis nis mail.aliases",
				sizeof(buf));
			(void) makemapentry(buf);
		}
#endif /* NIS */
#if NETINFO
		else if (strcmp(maptype[i], "netinfo") == 0 &&
			 stab("aliases.netinfo", ST_MAP, ST_FIND) == NULL)
		{
			(void) sm_strlcpy(buf, "aliases.netinfo netinfo -z, /aliases",
				sizeof(buf));
			(void) makemapentry(buf);
		}
#endif /* NETINFO */
#if HESIOD
		else if (strcmp(maptype[i], "hesiod") == 0 &&
			 stab("aliases.hesiod", ST_MAP, ST_FIND) == NULL)
		{
			(void) sm_strlcpy(buf, "aliases.hesiod hesiod aliases",
				sizeof(buf));
			(void) makemapentry(buf);
		}
#endif /* HESIOD */
#if LDAPMAP && defined(SUN_EXTENSIONS) && \
    defined(SUN_SIMPLIFIED_LDAP) && HASLDAPGETALIASBYNAME
		else if (strcmp(maptype[i], "ldap") == 0 &&
		    stab("aliases.ldap", ST_MAP, ST_FIND) == NULL)
		{
			(void) sm_strlcpy(buf, "aliases.ldap ldap -b . -h localhost -k mail=%0 -v mailgroup",
				sizeof buf);
			(void) makemapentry(buf);
		}
#endif /* LDAPMAP && defined(SUN_EXTENSIONS) && ... */
	}
	if (stab("aliases", ST_MAP, ST_FIND) == NULL)
	{
		(void) sm_strlcpy(buf, "aliases switch aliases", sizeof(buf));
		(void) makemapentry(buf);
	}
}