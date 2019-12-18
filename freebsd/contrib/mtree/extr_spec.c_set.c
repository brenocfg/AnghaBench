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
typedef  void* uid_t ;
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  nlink_t ;
typedef  void* gid_t ;
struct TYPE_4__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_5__ {int flags; int /*<<< orphan*/ * sha512digest; int /*<<< orphan*/ * sha384digest; int /*<<< orphan*/ * sha256digest; void* st_uid; int /*<<< orphan*/  type; TYPE_1__ st_mtimespec; int /*<<< orphan*/ * tags; int /*<<< orphan*/ * slink; int /*<<< orphan*/  st_size; int /*<<< orphan*/ * sha1digest; int /*<<< orphan*/ * rmd160digest; int /*<<< orphan*/  st_nlink; int /*<<< orphan*/  st_mode; int /*<<< orphan*/ * md5digest; void* st_gid; int /*<<< orphan*/  st_flags; int /*<<< orphan*/  st_rdev; int /*<<< orphan*/  cksum; } ;
typedef  TYPE_2__ NODE ;

/* Variables and functions */
#define  F_CKSUM 147 
#define  F_DEV 146 
#define  F_FLAGS 145 
#define  F_GID 144 
#define  F_GNAME 143 
#define  F_MD5 142 
#define  F_MODE 141 
#define  F_NLINK 140 
#define  F_RMD160 139 
#define  F_SHA1 138 
#define  F_SHA256 137 
#define  F_SHA384 136 
#define  F_SHA512 135 
#define  F_SIZE 134 
#define  F_SLINK 133 
#define  F_TAGS 132 
#define  F_TIME 131 
#define  F_TYPE 130 
#define  F_UID 129 
#define  F_UNAME 128 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  getmode (void*,int /*<<< orphan*/ ) ; 
 int gid_from_group (char*,void**) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  mtree_Wflag ; 
 int /*<<< orphan*/  mtree_err (char*,...) ; 
 int /*<<< orphan*/  parsedev (char*) ; 
 int parsekey (char*,int*) ; 
 int /*<<< orphan*/  parsetype (char*) ; 
 void* setmode (char*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,int,char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 void* strdup (char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_to_flags (char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  strtol (char*,char**,int) ; 
 int /*<<< orphan*/  strtoll (char*,char**,int) ; 
 int /*<<< orphan*/  strtoul (char*,char**,int) ; 
 int strunvis (int /*<<< orphan*/ *,char*) ; 
 int uid_from_user (char*,void**) ; 

__attribute__((used)) static void
set(char *t, NODE *ip)
{
	int	type, value, len;
	gid_t	gid;
	uid_t	uid;
	char	*kw, *val, *md, *ep;
	void	*m;

	while ((kw = strsep(&t, "= \t")) != NULL) {
		if (*kw == '\0')
			continue;
		if (strcmp(kw, "all") == 0)
			mtree_err("invalid keyword `all'");
		ip->flags |= type = parsekey(kw, &value);
		if (!value)
			/* Just set flag bit (F_IGN and F_OPT) */
			continue;
		while ((val = strsep(&t, " \t")) != NULL && *val == '\0')
			continue;
		if (val == NULL)
			mtree_err("missing value");
		switch (type) {
		case F_CKSUM:
			ip->cksum = strtoul(val, &ep, 10);
			if (*ep)
				mtree_err("invalid checksum `%s'", val);
			break;
		case F_DEV:
			ip->st_rdev = parsedev(val);
			break;
		case F_FLAGS:
			if (strcmp("none", val) == 0)
				ip->st_flags = 0;
			else if (string_to_flags(&val, &ip->st_flags, NULL)
			    != 0)
				mtree_err("invalid flag `%s'", val);
			break;
		case F_GID:
			ip->st_gid = (gid_t)strtoul(val, &ep, 10);
			if (*ep)
				mtree_err("invalid gid `%s'", val);
			break;
		case F_GNAME:
			if (mtree_Wflag)	/* don't parse if whacking */
				break;
			if (gid_from_group(val, &gid) == -1)
				mtree_err("unknown group `%s'", val);
			ip->st_gid = gid;
			break;
		case F_MD5:
			if (val[0]=='0' && val[1]=='x')
				md=&val[2];
			else
				md=val;
			if ((ip->md5digest = strdup(md)) == NULL)
				mtree_err("memory allocation error");
			break;
		case F_MODE:
			if ((m = setmode(val)) == NULL)
				mtree_err("cannot set file mode `%s' (%s)",
				    val, strerror(errno));
			ip->st_mode = getmode(m, 0);
			free(m);
			break;
		case F_NLINK:
			ip->st_nlink = (nlink_t)strtoul(val, &ep, 10);
			if (*ep)
				mtree_err("invalid link count `%s'", val);
			break;
		case F_RMD160:
			if (val[0]=='0' && val[1]=='x')
				md=&val[2];
			else
				md=val;
			if ((ip->rmd160digest = strdup(md)) == NULL)
				mtree_err("memory allocation error");
			break;
		case F_SHA1:
			if (val[0]=='0' && val[1]=='x')
				md=&val[2];
			else
				md=val;
			if ((ip->sha1digest = strdup(md)) == NULL)
				mtree_err("memory allocation error");
			break;
		case F_SIZE:
			ip->st_size = (off_t)strtoll(val, &ep, 10);
			if (*ep)
				mtree_err("invalid size `%s'", val);
			break;
		case F_SLINK:
			if ((ip->slink = strdup(val)) == NULL)
				mtree_err("memory allocation error");
			if (strunvis(ip->slink, val) == -1)
				mtree_err("strunvis failed on `%s'", val);
			break;
		case F_TAGS:
			len = strlen(val) + 3;	/* "," + str + ",\0" */
			if ((ip->tags = malloc(len)) == NULL)
				mtree_err("memory allocation error");
			snprintf(ip->tags, len, ",%s,", val);
			break;
		case F_TIME:
			ip->st_mtimespec.tv_sec =
			    (time_t)strtoll(val, &ep, 10);
			if (*ep != '.')
				mtree_err("invalid time `%s'", val);
			val = ep + 1;
			ip->st_mtimespec.tv_nsec = strtol(val, &ep, 10);
			if (*ep)
				mtree_err("invalid time `%s'", val);
			break;
		case F_TYPE:
			ip->type = parsetype(val);
			break;
		case F_UID:
			ip->st_uid = (uid_t)strtoul(val, &ep, 10);
			if (*ep)
				mtree_err("invalid uid `%s'", val);
			break;
		case F_UNAME:
			if (mtree_Wflag)	/* don't parse if whacking */
				break;
			if (uid_from_user(val, &uid) == -1)
				mtree_err("unknown user `%s'", val);
			ip->st_uid = uid;
			break;
		case F_SHA256:
			if (val[0]=='0' && val[1]=='x')
				md=&val[2];
			else
				md=val;
			if ((ip->sha256digest = strdup(md)) == NULL)
				mtree_err("memory allocation error");
			break;
		case F_SHA384:
			if (val[0]=='0' && val[1]=='x')
				md=&val[2];
			else
				md=val;
			if ((ip->sha384digest = strdup(md)) == NULL)
				mtree_err("memory allocation error");
			break;
		case F_SHA512:
			if (val[0]=='0' && val[1]=='x')
				md=&val[2];
			else
				md=val;
			if ((ip->sha512digest = strdup(md)) == NULL)
				mtree_err("memory allocation error");
			break;
		default:
			mtree_err(
			    "set(): unsupported key type 0x%x (INTERNAL ERROR)",
			    type);
			/* NOTREACHED */
		}
	}
}