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
struct TYPE_3__ {char* member_0; int member_1; } ;
typedef  TYPE_1__ zprop_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  PROP_DEFAULT ; 
 int /*<<< orphan*/  PROP_INHERIT ; 
 int /*<<< orphan*/  PROP_ONETIME ; 
 int /*<<< orphan*/  PROP_READONLY ; 
 int /*<<< orphan*/  PROP_TYPE_NUMBER ; 
 int /*<<< orphan*/  PROP_TYPE_STRING ; 
 int /*<<< orphan*/  SPA_OLD_MAXBLOCKSIZE ; 
#define  U8_TEXTPREP_NFC 191 
#define  U8_TEXTPREP_NFD 190 
#define  U8_TEXTPREP_NFKC 189 
#define  U8_TEXTPREP_NFKD 188 
 int /*<<< orphan*/  UINT64_MAX ; 
#define  ZFS_ACL_DISCARD 187 
#define  ZFS_ACL_GROUPMASK 186 
#define  ZFS_ACL_NOALLOW 185 
#define  ZFS_ACL_PASSTHROUGH 184 
#define  ZFS_ACL_PASSTHROUGH_X 183 
#define  ZFS_ACL_RESTRICTED 182 
#define  ZFS_CACHE_ALL 181 
#define  ZFS_CACHE_METADATA 180 
#define  ZFS_CACHE_NONE 179 
#define  ZFS_CANMOUNT_NOAUTO 178 
#define  ZFS_CANMOUNT_OFF 177 
#define  ZFS_CANMOUNT_ON 176 
#define  ZFS_CASE_INSENSITIVE 175 
#define  ZFS_CASE_MIXED 174 
#define  ZFS_CASE_SENSITIVE 173 
#define  ZFS_DNSIZE_16K 172 
#define  ZFS_DNSIZE_1K 171 
#define  ZFS_DNSIZE_2K 170 
#define  ZFS_DNSIZE_4K 169 
#define  ZFS_DNSIZE_8K 168 
#define  ZFS_DNSIZE_AUTO 167 
#define  ZFS_DNSIZE_LEGACY 166 
#define  ZFS_LOGBIAS_LATENCY 165 
#define  ZFS_LOGBIAS_THROUGHPUT 164 
 char* ZFS_MLSLABEL_DEFAULT ; 
 int /*<<< orphan*/  ZFS_PROP_ACLINHERIT ; 
 int /*<<< orphan*/  ZFS_PROP_ACLMODE ; 
 int /*<<< orphan*/  ZFS_PROP_ATIME ; 
 int /*<<< orphan*/  ZFS_PROP_AVAILABLE ; 
 int /*<<< orphan*/  ZFS_PROP_CANMOUNT ; 
 int /*<<< orphan*/  ZFS_PROP_CASE ; 
 int /*<<< orphan*/  ZFS_PROP_CHECKSUM ; 
 int /*<<< orphan*/  ZFS_PROP_CLONES ; 
 int /*<<< orphan*/  ZFS_PROP_COMPRESSION ; 
 int /*<<< orphan*/  ZFS_PROP_COMPRESSRATIO ; 
 int /*<<< orphan*/  ZFS_PROP_COPIES ; 
 int /*<<< orphan*/  ZFS_PROP_CREATETXG ; 
 int /*<<< orphan*/  ZFS_PROP_CREATION ; 
 int /*<<< orphan*/  ZFS_PROP_DEDUP ; 
 int /*<<< orphan*/  ZFS_PROP_DEFER_DESTROY ; 
 int /*<<< orphan*/  ZFS_PROP_DEVICES ; 
 int /*<<< orphan*/  ZFS_PROP_DNODESIZE ; 
 int /*<<< orphan*/  ZFS_PROP_EXEC ; 
 int /*<<< orphan*/  ZFS_PROP_FILESYSTEM_COUNT ; 
 int /*<<< orphan*/  ZFS_PROP_FILESYSTEM_LIMIT ; 
 int /*<<< orphan*/  ZFS_PROP_GUID ; 
 int /*<<< orphan*/  ZFS_PROP_INCONSISTENT ; 
 int /*<<< orphan*/  ZFS_PROP_ISCSIOPTIONS ; 
 int /*<<< orphan*/  ZFS_PROP_LOGBIAS ; 
 int /*<<< orphan*/  ZFS_PROP_LOGICALREFERENCED ; 
 int /*<<< orphan*/  ZFS_PROP_LOGICALUSED ; 
 int /*<<< orphan*/  ZFS_PROP_MLSLABEL ; 
 int /*<<< orphan*/  ZFS_PROP_MOUNTED ; 
 int /*<<< orphan*/  ZFS_PROP_MOUNTPOINT ; 
 int /*<<< orphan*/  ZFS_PROP_NAME ; 
 int /*<<< orphan*/  ZFS_PROP_NBMAND ; 
 int /*<<< orphan*/  ZFS_PROP_NORMALIZE ; 
 int /*<<< orphan*/  ZFS_PROP_NUMCLONES ; 
 int /*<<< orphan*/  ZFS_PROP_OBJSETID ; 
 int /*<<< orphan*/  ZFS_PROP_ORIGIN ; 
 int /*<<< orphan*/  ZFS_PROP_PREV_SNAP ; 
 int /*<<< orphan*/  ZFS_PROP_PRIMARYCACHE ; 
 int /*<<< orphan*/  ZFS_PROP_QUOTA ; 
 int /*<<< orphan*/  ZFS_PROP_READONLY ; 
 int /*<<< orphan*/  ZFS_PROP_RECEIVE_RESUME_TOKEN ; 
 int /*<<< orphan*/  ZFS_PROP_RECORDSIZE ; 
 int /*<<< orphan*/  ZFS_PROP_REDUNDANT_METADATA ; 
 int /*<<< orphan*/  ZFS_PROP_REFERENCED ; 
 int /*<<< orphan*/  ZFS_PROP_REFQUOTA ; 
 int /*<<< orphan*/  ZFS_PROP_REFRATIO ; 
 int /*<<< orphan*/  ZFS_PROP_REFRESERVATION ; 
 int /*<<< orphan*/  ZFS_PROP_REMAPTXG ; 
 int /*<<< orphan*/  ZFS_PROP_RESERVATION ; 
 int /*<<< orphan*/  ZFS_PROP_SECONDARYCACHE ; 
 int /*<<< orphan*/  ZFS_PROP_SETUID ; 
 int /*<<< orphan*/  ZFS_PROP_SHARENFS ; 
 int /*<<< orphan*/  ZFS_PROP_SHARESMB ; 
 int /*<<< orphan*/  ZFS_PROP_SNAPDIR ; 
 int /*<<< orphan*/  ZFS_PROP_SNAPSHOT_COUNT ; 
 int /*<<< orphan*/  ZFS_PROP_SNAPSHOT_LIMIT ; 
 int /*<<< orphan*/  ZFS_PROP_STMF_SHAREINFO ; 
 int /*<<< orphan*/  ZFS_PROP_SYNC ; 
 int /*<<< orphan*/  ZFS_PROP_TYPE ; 
 int /*<<< orphan*/  ZFS_PROP_UNIQUE ; 
 int /*<<< orphan*/  ZFS_PROP_USED ; 
 int /*<<< orphan*/  ZFS_PROP_USEDCHILD ; 
 int /*<<< orphan*/  ZFS_PROP_USEDDS ; 
 int /*<<< orphan*/  ZFS_PROP_USEDREFRESERV ; 
 int /*<<< orphan*/  ZFS_PROP_USEDSNAP ; 
 int /*<<< orphan*/  ZFS_PROP_USERACCOUNTING ; 
 int /*<<< orphan*/  ZFS_PROP_USERREFS ; 
 int /*<<< orphan*/  ZFS_PROP_UTF8ONLY ; 
 int /*<<< orphan*/  ZFS_PROP_VERSION ; 
 int /*<<< orphan*/  ZFS_PROP_VOLBLOCKSIZE ; 
 int /*<<< orphan*/  ZFS_PROP_VOLMODE ; 
 int /*<<< orphan*/  ZFS_PROP_VOLSIZE ; 
 int /*<<< orphan*/  ZFS_PROP_VSCAN ; 
 int /*<<< orphan*/  ZFS_PROP_WRITTEN ; 
 int /*<<< orphan*/  ZFS_PROP_XATTR ; 
 int /*<<< orphan*/  ZFS_PROP_ZONED ; 
#define  ZFS_REDUNDANT_METADATA_ALL 163 
#define  ZFS_REDUNDANT_METADATA_MOST 162 
#define  ZFS_SNAPDIR_HIDDEN 161 
#define  ZFS_SNAPDIR_VISIBLE 160 
#define  ZFS_SYNC_ALWAYS 159 
#define  ZFS_SYNC_DISABLED 158 
#define  ZFS_SYNC_STANDARD 157 
 int ZFS_TYPE_BOOKMARK ; 
 int ZFS_TYPE_DATASET ; 
 int ZFS_TYPE_FILESYSTEM ; 
 int ZFS_TYPE_SNAPSHOT ; 
 int ZFS_TYPE_VOLUME ; 
#define  ZFS_VOLMODE_DEFAULT 156 
#define  ZFS_VOLMODE_DEV 155 
#define  ZFS_VOLMODE_GEOM 154 
#define  ZFS_VOLMODE_NONE 153 
 int const ZIO_CHECKSUM_DEFAULT ; 
#define  ZIO_CHECKSUM_EDONR 152 
#define  ZIO_CHECKSUM_FLETCHER_2 151 
#define  ZIO_CHECKSUM_FLETCHER_4 150 
#define  ZIO_CHECKSUM_NOPARITY 149 
#define  ZIO_CHECKSUM_OFF 148 
#define  ZIO_CHECKSUM_ON 147 
#define  ZIO_CHECKSUM_SHA256 146 
#define  ZIO_CHECKSUM_SHA512 145 
#define  ZIO_CHECKSUM_SKEIN 144 
#define  ZIO_CHECKSUM_VERIFY 143 
 int const ZIO_COMPRESS_DEFAULT ; 
#define  ZIO_COMPRESS_GZIP_1 142 
#define  ZIO_COMPRESS_GZIP_2 141 
#define  ZIO_COMPRESS_GZIP_3 140 
#define  ZIO_COMPRESS_GZIP_4 139 
#define  ZIO_COMPRESS_GZIP_5 138 
#define  ZIO_COMPRESS_GZIP_6 137 
#define  ZIO_COMPRESS_GZIP_7 136 
#define  ZIO_COMPRESS_GZIP_8 135 
#define  ZIO_COMPRESS_GZIP_9 134 
#define  ZIO_COMPRESS_LZ4 133 
#define  ZIO_COMPRESS_LZJB 132 
#define  ZIO_COMPRESS_OFF 131 
#define  ZIO_COMPRESS_ON 130 
#define  ZIO_COMPRESS_ZLE 129 
#define  ZPL_VERSION 128 
 int /*<<< orphan*/  ZVOL_DEFAULT_BLOCKSIZE ; 
 int /*<<< orphan*/  zprop_register_hidden (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  zprop_register_impl (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zprop_register_index (int /*<<< orphan*/ ,char*,int const,int /*<<< orphan*/ ,int,char*,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  zprop_register_number (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  zprop_register_string (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int,char*,char*) ; 

void
zfs_prop_init(void)
{
	static zprop_index_t checksum_table[] = {
		{ "on",		ZIO_CHECKSUM_ON },
		{ "off",	ZIO_CHECKSUM_OFF },
		{ "fletcher2",	ZIO_CHECKSUM_FLETCHER_2 },
		{ "fletcher4",	ZIO_CHECKSUM_FLETCHER_4 },
		{ "sha256",	ZIO_CHECKSUM_SHA256 },
		{ "noparity",	ZIO_CHECKSUM_NOPARITY },
		{ "sha512",	ZIO_CHECKSUM_SHA512 },
		{ "skein",	ZIO_CHECKSUM_SKEIN },
#ifdef illumos
		{ "edonr",	ZIO_CHECKSUM_EDONR },
#endif
		{ NULL }
	};

	static zprop_index_t dedup_table[] = {
		{ "on",		ZIO_CHECKSUM_ON },
		{ "off",	ZIO_CHECKSUM_OFF },
		{ "verify",	ZIO_CHECKSUM_ON | ZIO_CHECKSUM_VERIFY },
		{ "sha256",	ZIO_CHECKSUM_SHA256 },
		{ "sha256,verify",
				ZIO_CHECKSUM_SHA256 | ZIO_CHECKSUM_VERIFY },
		{ "sha512",	ZIO_CHECKSUM_SHA512 },
		{ "sha512,verify",
				ZIO_CHECKSUM_SHA512 | ZIO_CHECKSUM_VERIFY },
		{ "skein",	ZIO_CHECKSUM_SKEIN },
		{ "skein,verify",
				ZIO_CHECKSUM_SKEIN | ZIO_CHECKSUM_VERIFY },
#ifdef illumos
		{ "edonr,verify",
				ZIO_CHECKSUM_EDONR | ZIO_CHECKSUM_VERIFY },
#endif
		{ NULL }
	};

	static zprop_index_t compress_table[] = {
		{ "on",		ZIO_COMPRESS_ON },
		{ "off",	ZIO_COMPRESS_OFF },
		{ "lzjb",	ZIO_COMPRESS_LZJB },
		{ "gzip",	ZIO_COMPRESS_GZIP_6 },	/* gzip default */
		{ "gzip-1",	ZIO_COMPRESS_GZIP_1 },
		{ "gzip-2",	ZIO_COMPRESS_GZIP_2 },
		{ "gzip-3",	ZIO_COMPRESS_GZIP_3 },
		{ "gzip-4",	ZIO_COMPRESS_GZIP_4 },
		{ "gzip-5",	ZIO_COMPRESS_GZIP_5 },
		{ "gzip-6",	ZIO_COMPRESS_GZIP_6 },
		{ "gzip-7",	ZIO_COMPRESS_GZIP_7 },
		{ "gzip-8",	ZIO_COMPRESS_GZIP_8 },
		{ "gzip-9",	ZIO_COMPRESS_GZIP_9 },
		{ "zle",	ZIO_COMPRESS_ZLE },
		{ "lz4",	ZIO_COMPRESS_LZ4 },
		{ NULL }
	};

	static zprop_index_t snapdir_table[] = {
		{ "hidden",	ZFS_SNAPDIR_HIDDEN },
		{ "visible",	ZFS_SNAPDIR_VISIBLE },
		{ NULL }
	};

	static zprop_index_t acl_mode_table[] = {
		{ "discard",	ZFS_ACL_DISCARD },
		{ "groupmask",	ZFS_ACL_GROUPMASK },
		{ "passthrough", ZFS_ACL_PASSTHROUGH },
		{ "restricted", ZFS_ACL_RESTRICTED },
		{ NULL }
	};

	static zprop_index_t acl_inherit_table[] = {
		{ "discard",	ZFS_ACL_DISCARD },
		{ "noallow",	ZFS_ACL_NOALLOW },
		{ "restricted",	ZFS_ACL_RESTRICTED },
		{ "passthrough", ZFS_ACL_PASSTHROUGH },
		{ "secure",	ZFS_ACL_RESTRICTED }, /* bkwrd compatability */
		{ "passthrough-x", ZFS_ACL_PASSTHROUGH_X },
		{ NULL }
	};

	static zprop_index_t case_table[] = {
		{ "sensitive",		ZFS_CASE_SENSITIVE },
		{ "insensitive",	ZFS_CASE_INSENSITIVE },
		{ "mixed",		ZFS_CASE_MIXED },
		{ NULL }
	};

	static zprop_index_t copies_table[] = {
		{ "1",		1 },
		{ "2",		2 },
		{ "3",		3 },
		{ NULL }
	};

	/*
	 * Use the unique flags we have to send to u8_strcmp() and/or
	 * u8_textprep() to represent the various normalization property
	 * values.
	 */
	static zprop_index_t normalize_table[] = {
		{ "none",	0 },
		{ "formD",	U8_TEXTPREP_NFD },
		{ "formKC",	U8_TEXTPREP_NFKC },
		{ "formC",	U8_TEXTPREP_NFC },
		{ "formKD",	U8_TEXTPREP_NFKD },
		{ NULL }
	};

	static zprop_index_t version_table[] = {
		{ "1",		1 },
		{ "2",		2 },
		{ "3",		3 },
		{ "4",		4 },
		{ "5",		5 },
		{ "current",	ZPL_VERSION },
		{ NULL }
	};

	static zprop_index_t boolean_table[] = {
		{ "off",	0 },
		{ "on",		1 },
		{ NULL }
	};

	static zprop_index_t logbias_table[] = {
		{ "latency",	ZFS_LOGBIAS_LATENCY },
		{ "throughput",	ZFS_LOGBIAS_THROUGHPUT },
		{ NULL }
	};

	static zprop_index_t canmount_table[] = {
		{ "off",	ZFS_CANMOUNT_OFF },
		{ "on",		ZFS_CANMOUNT_ON },
		{ "noauto",	ZFS_CANMOUNT_NOAUTO },
		{ NULL }
	};

	static zprop_index_t cache_table[] = {
		{ "none",	ZFS_CACHE_NONE },
		{ "metadata",	ZFS_CACHE_METADATA },
		{ "all",	ZFS_CACHE_ALL },
		{ NULL }
	};

	static zprop_index_t sync_table[] = {
		{ "standard",	ZFS_SYNC_STANDARD },
		{ "always",	ZFS_SYNC_ALWAYS },
		{ "disabled",	ZFS_SYNC_DISABLED },
		{ NULL }
	};

	static zprop_index_t volmode_table[] = {
		{ "default",	ZFS_VOLMODE_DEFAULT },
		{ "geom",	ZFS_VOLMODE_GEOM },
		{ "dev",	ZFS_VOLMODE_DEV },
		{ "none",	ZFS_VOLMODE_NONE },
		{ NULL }
	};

	static zprop_index_t dnsize_table[] = {
		{ "legacy",	ZFS_DNSIZE_LEGACY },
		{ "auto",	ZFS_DNSIZE_AUTO },
		{ "1k",		ZFS_DNSIZE_1K },
		{ "2k",		ZFS_DNSIZE_2K },
		{ "4k",		ZFS_DNSIZE_4K },
		{ "8k",		ZFS_DNSIZE_8K },
		{ "16k",	ZFS_DNSIZE_16K },
		{ NULL }
	};

	static zprop_index_t redundant_metadata_table[] = {
		{ "all",	ZFS_REDUNDANT_METADATA_ALL },
		{ "most",	ZFS_REDUNDANT_METADATA_MOST },
		{ NULL }
	};

	/* inherit index properties */
	zprop_register_index(ZFS_PROP_REDUNDANT_METADATA, "redundant_metadata",
	    ZFS_REDUNDANT_METADATA_ALL,
	    PROP_INHERIT, ZFS_TYPE_FILESYSTEM | ZFS_TYPE_VOLUME,
	    "all | most", "REDUND_MD",
	    redundant_metadata_table);
	zprop_register_index(ZFS_PROP_SYNC, "sync", ZFS_SYNC_STANDARD,
	    PROP_INHERIT, ZFS_TYPE_FILESYSTEM | ZFS_TYPE_VOLUME,
	    "standard | always | disabled", "SYNC",
	    sync_table);
	zprop_register_index(ZFS_PROP_CHECKSUM, "checksum",
	    ZIO_CHECKSUM_DEFAULT, PROP_INHERIT, ZFS_TYPE_FILESYSTEM |
	    ZFS_TYPE_VOLUME,
	    "on | off | fletcher2 | fletcher4 | sha256 | sha512 | "
	    "skein", "CHECKSUM", checksum_table);
	zprop_register_index(ZFS_PROP_DEDUP, "dedup", ZIO_CHECKSUM_OFF,
	    PROP_INHERIT, ZFS_TYPE_FILESYSTEM | ZFS_TYPE_VOLUME,
	    "on | off | verify | sha256[,verify], sha512[,verify], "
	    "skein[,verify]", "DEDUP", dedup_table);
	zprop_register_index(ZFS_PROP_COMPRESSION, "compression",
	    ZIO_COMPRESS_DEFAULT, PROP_INHERIT,
	    ZFS_TYPE_FILESYSTEM | ZFS_TYPE_VOLUME,
	    "on | off | lzjb | gzip | gzip-[1-9] | zle | lz4",
	    "COMPRESS", compress_table);
	zprop_register_index(ZFS_PROP_SNAPDIR, "snapdir", ZFS_SNAPDIR_HIDDEN,
	    PROP_INHERIT, ZFS_TYPE_FILESYSTEM,
	    "hidden | visible", "SNAPDIR", snapdir_table);
	zprop_register_index(ZFS_PROP_ACLMODE, "aclmode", ZFS_ACL_DISCARD,
	    PROP_INHERIT, ZFS_TYPE_FILESYSTEM,
	    "discard | groupmask | passthrough | restricted", "ACLMODE",
	    acl_mode_table);
	zprop_register_index(ZFS_PROP_ACLINHERIT, "aclinherit",
	    ZFS_ACL_RESTRICTED, PROP_INHERIT, ZFS_TYPE_FILESYSTEM,
	    "discard | noallow | restricted | passthrough | passthrough-x",
	    "ACLINHERIT", acl_inherit_table);
	zprop_register_index(ZFS_PROP_COPIES, "copies", 1, PROP_INHERIT,
	    ZFS_TYPE_FILESYSTEM | ZFS_TYPE_VOLUME,
	    "1 | 2 | 3", "COPIES", copies_table);
	zprop_register_index(ZFS_PROP_PRIMARYCACHE, "primarycache",
	    ZFS_CACHE_ALL, PROP_INHERIT,
	    ZFS_TYPE_FILESYSTEM | ZFS_TYPE_SNAPSHOT | ZFS_TYPE_VOLUME,
	    "all | none | metadata", "PRIMARYCACHE", cache_table);
	zprop_register_index(ZFS_PROP_SECONDARYCACHE, "secondarycache",
	    ZFS_CACHE_ALL, PROP_INHERIT,
	    ZFS_TYPE_FILESYSTEM | ZFS_TYPE_SNAPSHOT | ZFS_TYPE_VOLUME,
	    "all | none | metadata", "SECONDARYCACHE", cache_table);
	zprop_register_index(ZFS_PROP_LOGBIAS, "logbias", ZFS_LOGBIAS_LATENCY,
	    PROP_INHERIT, ZFS_TYPE_FILESYSTEM | ZFS_TYPE_VOLUME,
	    "latency | throughput", "LOGBIAS", logbias_table);
	zprop_register_index(ZFS_PROP_VOLMODE, "volmode",
	    ZFS_VOLMODE_DEFAULT, PROP_INHERIT,
	    ZFS_TYPE_FILESYSTEM | ZFS_TYPE_SNAPSHOT | ZFS_TYPE_VOLUME,
	    "default | geom | dev | none", "VOLMODE", volmode_table);
 
	zprop_register_index(ZFS_PROP_DNODESIZE, "dnodesize",
	    ZFS_DNSIZE_LEGACY, PROP_INHERIT, ZFS_TYPE_FILESYSTEM,
	    "legacy | auto | 1k | 2k | 4k | 8k | 16k", "DNSIZE", dnsize_table);

	/* inherit index (boolean) properties */
	zprop_register_index(ZFS_PROP_ATIME, "atime", 1, PROP_INHERIT,
	    ZFS_TYPE_FILESYSTEM, "on | off", "ATIME", boolean_table);
	zprop_register_index(ZFS_PROP_DEVICES, "devices", 1, PROP_INHERIT,
	    ZFS_TYPE_FILESYSTEM | ZFS_TYPE_SNAPSHOT, "on | off", "DEVICES",
	    boolean_table);
	zprop_register_index(ZFS_PROP_EXEC, "exec", 1, PROP_INHERIT,
	    ZFS_TYPE_FILESYSTEM | ZFS_TYPE_SNAPSHOT, "on | off", "EXEC",
	    boolean_table);
	zprop_register_index(ZFS_PROP_SETUID, "setuid", 1, PROP_INHERIT,
	    ZFS_TYPE_FILESYSTEM | ZFS_TYPE_SNAPSHOT, "on | off", "SETUID",
	    boolean_table);
	zprop_register_index(ZFS_PROP_READONLY, "readonly", 0, PROP_INHERIT,
	    ZFS_TYPE_FILESYSTEM | ZFS_TYPE_VOLUME, "on | off", "RDONLY",
	    boolean_table);
	zprop_register_index(ZFS_PROP_ZONED, "jailed", 0, PROP_INHERIT,
	    ZFS_TYPE_FILESYSTEM, "on | off", "JAILED", boolean_table);
	zprop_register_index(ZFS_PROP_XATTR, "xattr", 1, PROP_INHERIT,
	    ZFS_TYPE_FILESYSTEM | ZFS_TYPE_SNAPSHOT, "on | off", "XATTR",
	    boolean_table);
	zprop_register_index(ZFS_PROP_VSCAN, "vscan", 0, PROP_INHERIT,
	    ZFS_TYPE_FILESYSTEM, "on | off", "VSCAN",
	    boolean_table);
	zprop_register_index(ZFS_PROP_NBMAND, "nbmand", 0, PROP_INHERIT,
	    ZFS_TYPE_FILESYSTEM | ZFS_TYPE_SNAPSHOT, "on | off", "NBMAND",
	    boolean_table);

	/* default index properties */
	zprop_register_index(ZFS_PROP_VERSION, "version", 0, PROP_DEFAULT,
	    ZFS_TYPE_FILESYSTEM | ZFS_TYPE_SNAPSHOT,
	    "1 | 2 | 3 | 4 | 5 | current", "VERSION", version_table);
	zprop_register_index(ZFS_PROP_CANMOUNT, "canmount", ZFS_CANMOUNT_ON,
	    PROP_DEFAULT, ZFS_TYPE_FILESYSTEM, "on | off | noauto",
	    "CANMOUNT", canmount_table);

	/* readonly index (boolean) properties */
	zprop_register_index(ZFS_PROP_MOUNTED, "mounted", 0, PROP_READONLY,
	    ZFS_TYPE_FILESYSTEM, "yes | no", "MOUNTED", boolean_table);
	zprop_register_index(ZFS_PROP_DEFER_DESTROY, "defer_destroy", 0,
	    PROP_READONLY, ZFS_TYPE_SNAPSHOT, "yes | no", "DEFER_DESTROY",
	    boolean_table);

	/* set once index properties */
	zprop_register_index(ZFS_PROP_NORMALIZE, "normalization", 0,
	    PROP_ONETIME, ZFS_TYPE_FILESYSTEM | ZFS_TYPE_SNAPSHOT,
	    "none | formC | formD | formKC | formKD", "NORMALIZATION",
	    normalize_table);
	zprop_register_index(ZFS_PROP_CASE, "casesensitivity",
	    ZFS_CASE_SENSITIVE, PROP_ONETIME, ZFS_TYPE_FILESYSTEM |
	    ZFS_TYPE_SNAPSHOT,
	    "sensitive | insensitive | mixed", "CASE", case_table);

	/* set once index (boolean) properties */
	zprop_register_index(ZFS_PROP_UTF8ONLY, "utf8only", 0, PROP_ONETIME,
	    ZFS_TYPE_FILESYSTEM | ZFS_TYPE_SNAPSHOT,
	    "on | off", "UTF8ONLY", boolean_table);

	/* string properties */
	zprop_register_string(ZFS_PROP_ORIGIN, "origin", NULL, PROP_READONLY,
	    ZFS_TYPE_FILESYSTEM | ZFS_TYPE_VOLUME, "<snapshot>", "ORIGIN");
	zprop_register_string(ZFS_PROP_CLONES, "clones", NULL, PROP_READONLY,
	    ZFS_TYPE_SNAPSHOT, "<dataset>[,...]", "CLONES");
	zprop_register_string(ZFS_PROP_MOUNTPOINT, "mountpoint", "/",
	    PROP_INHERIT, ZFS_TYPE_FILESYSTEM, "<path> | legacy | none",
	    "MOUNTPOINT");
	zprop_register_string(ZFS_PROP_SHARENFS, "sharenfs", "off",
	    PROP_INHERIT, ZFS_TYPE_FILESYSTEM, "on | off | share(1M) options",
	    "SHARENFS");
	zprop_register_string(ZFS_PROP_TYPE, "type", NULL, PROP_READONLY,
	    ZFS_TYPE_DATASET | ZFS_TYPE_BOOKMARK,
	    "filesystem | volume | snapshot | bookmark", "TYPE");
	zprop_register_string(ZFS_PROP_SHARESMB, "sharesmb", "off",
	    PROP_INHERIT, ZFS_TYPE_FILESYSTEM,
	    "on | off | sharemgr(1M) options", "SHARESMB");
	zprop_register_string(ZFS_PROP_MLSLABEL, "mlslabel",
	    ZFS_MLSLABEL_DEFAULT, PROP_INHERIT, ZFS_TYPE_DATASET,
	    "<sensitivity label>", "MLSLABEL");
	zprop_register_string(ZFS_PROP_RECEIVE_RESUME_TOKEN,
	    "receive_resume_token",
	    NULL, PROP_READONLY, ZFS_TYPE_FILESYSTEM | ZFS_TYPE_VOLUME,
	    "<string token>", "RESUMETOK");

	/* readonly number properties */
	zprop_register_number(ZFS_PROP_USED, "used", 0, PROP_READONLY,
	    ZFS_TYPE_DATASET, "<size>", "USED");
	zprop_register_number(ZFS_PROP_AVAILABLE, "available", 0, PROP_READONLY,
	    ZFS_TYPE_FILESYSTEM | ZFS_TYPE_VOLUME, "<size>", "AVAIL");
	zprop_register_number(ZFS_PROP_REFERENCED, "referenced", 0,
	    PROP_READONLY, ZFS_TYPE_DATASET, "<size>", "REFER");
	zprop_register_number(ZFS_PROP_COMPRESSRATIO, "compressratio", 0,
	    PROP_READONLY, ZFS_TYPE_DATASET,
	    "<1.00x or higher if compressed>", "RATIO");
	zprop_register_number(ZFS_PROP_REFRATIO, "refcompressratio", 0,
	    PROP_READONLY, ZFS_TYPE_DATASET,
	    "<1.00x or higher if compressed>", "REFRATIO");
	zprop_register_number(ZFS_PROP_VOLBLOCKSIZE, "volblocksize",
	    ZVOL_DEFAULT_BLOCKSIZE, PROP_ONETIME,
	    ZFS_TYPE_VOLUME, "512 to 128k, power of 2",	"VOLBLOCK");
	zprop_register_number(ZFS_PROP_USEDSNAP, "usedbysnapshots", 0,
	    PROP_READONLY, ZFS_TYPE_FILESYSTEM | ZFS_TYPE_VOLUME, "<size>",
	    "USEDSNAP");
	zprop_register_number(ZFS_PROP_USEDDS, "usedbydataset", 0,
	    PROP_READONLY, ZFS_TYPE_FILESYSTEM | ZFS_TYPE_VOLUME, "<size>",
	    "USEDDS");
	zprop_register_number(ZFS_PROP_USEDCHILD, "usedbychildren", 0,
	    PROP_READONLY, ZFS_TYPE_FILESYSTEM | ZFS_TYPE_VOLUME, "<size>",
	    "USEDCHILD");
	zprop_register_number(ZFS_PROP_USEDREFRESERV, "usedbyrefreservation", 0,
	    PROP_READONLY,
	    ZFS_TYPE_FILESYSTEM | ZFS_TYPE_VOLUME, "<size>", "USEDREFRESERV");
	zprop_register_number(ZFS_PROP_USERREFS, "userrefs", 0, PROP_READONLY,
	    ZFS_TYPE_SNAPSHOT, "<count>", "USERREFS");
	zprop_register_number(ZFS_PROP_WRITTEN, "written", 0, PROP_READONLY,
	    ZFS_TYPE_DATASET, "<size>", "WRITTEN");
	zprop_register_number(ZFS_PROP_LOGICALUSED, "logicalused", 0,
	    PROP_READONLY, ZFS_TYPE_FILESYSTEM | ZFS_TYPE_VOLUME, "<size>",
	    "LUSED");
	zprop_register_number(ZFS_PROP_LOGICALREFERENCED, "logicalreferenced",
	    0, PROP_READONLY, ZFS_TYPE_DATASET, "<size>", "LREFER");

	/* default number properties */
	zprop_register_number(ZFS_PROP_QUOTA, "quota", 0, PROP_DEFAULT,
	    ZFS_TYPE_FILESYSTEM, "<size> | none", "QUOTA");
	zprop_register_number(ZFS_PROP_RESERVATION, "reservation", 0,
	    PROP_DEFAULT, ZFS_TYPE_FILESYSTEM | ZFS_TYPE_VOLUME,
	    "<size> | none", "RESERV");
	zprop_register_number(ZFS_PROP_VOLSIZE, "volsize", 0, PROP_DEFAULT,
	    ZFS_TYPE_VOLUME, "<size>", "VOLSIZE");
	zprop_register_number(ZFS_PROP_REFQUOTA, "refquota", 0, PROP_DEFAULT,
	    ZFS_TYPE_FILESYSTEM, "<size> | none", "REFQUOTA");
	zprop_register_number(ZFS_PROP_REFRESERVATION, "refreservation", 0,
	    PROP_DEFAULT, ZFS_TYPE_FILESYSTEM | ZFS_TYPE_VOLUME,
	    "<size> | none", "REFRESERV");
	zprop_register_number(ZFS_PROP_FILESYSTEM_LIMIT, "filesystem_limit",
	    UINT64_MAX, PROP_DEFAULT, ZFS_TYPE_FILESYSTEM,
	    "<count> | none", "FSLIMIT");
	zprop_register_number(ZFS_PROP_SNAPSHOT_LIMIT, "snapshot_limit",
	    UINT64_MAX, PROP_DEFAULT, ZFS_TYPE_FILESYSTEM | ZFS_TYPE_VOLUME,
	    "<count> | none", "SSLIMIT");
	zprop_register_number(ZFS_PROP_FILESYSTEM_COUNT, "filesystem_count",
	    UINT64_MAX, PROP_DEFAULT, ZFS_TYPE_FILESYSTEM,
	    "<count>", "FSCOUNT");
	zprop_register_number(ZFS_PROP_SNAPSHOT_COUNT, "snapshot_count",
	    UINT64_MAX, PROP_DEFAULT, ZFS_TYPE_FILESYSTEM | ZFS_TYPE_VOLUME,
	    "<count>", "SSCOUNT");
	zprop_register_number(ZFS_PROP_GUID, "guid", 0, PROP_READONLY,
	    ZFS_TYPE_DATASET | ZFS_TYPE_BOOKMARK, "<uint64>", "GUID");
	zprop_register_number(ZFS_PROP_CREATETXG, "createtxg", 0, PROP_READONLY,
	    ZFS_TYPE_DATASET | ZFS_TYPE_BOOKMARK, "<uint64>", "CREATETXG");

	/* inherit number properties */
	zprop_register_number(ZFS_PROP_RECORDSIZE, "recordsize",
	    SPA_OLD_MAXBLOCKSIZE, PROP_INHERIT,
	    ZFS_TYPE_FILESYSTEM, "512 to 1M, power of 2", "RECSIZE");

	/* hidden properties */
	zprop_register_hidden(ZFS_PROP_REMAPTXG, "remaptxg", PROP_TYPE_NUMBER,
	    PROP_READONLY, ZFS_TYPE_DATASET, "REMAPTXG");
	zprop_register_hidden(ZFS_PROP_NUMCLONES, "numclones", PROP_TYPE_NUMBER,
	    PROP_READONLY, ZFS_TYPE_SNAPSHOT, "NUMCLONES");
	zprop_register_hidden(ZFS_PROP_NAME, "name", PROP_TYPE_STRING,
	    PROP_READONLY, ZFS_TYPE_DATASET | ZFS_TYPE_BOOKMARK, "NAME");
	zprop_register_hidden(ZFS_PROP_ISCSIOPTIONS, "iscsioptions",
	    PROP_TYPE_STRING, PROP_INHERIT, ZFS_TYPE_VOLUME, "ISCSIOPTIONS");
	zprop_register_hidden(ZFS_PROP_STMF_SHAREINFO, "stmf_sbd_lu",
	    PROP_TYPE_STRING, PROP_INHERIT, ZFS_TYPE_VOLUME,
	    "STMF_SBD_LU");
	zprop_register_hidden(ZFS_PROP_USERACCOUNTING, "useraccounting",
	    PROP_TYPE_NUMBER, PROP_READONLY, ZFS_TYPE_DATASET,
	    "USERACCOUNTING");
	zprop_register_hidden(ZFS_PROP_UNIQUE, "unique", PROP_TYPE_NUMBER,
	    PROP_READONLY, ZFS_TYPE_DATASET, "UNIQUE");
	zprop_register_hidden(ZFS_PROP_OBJSETID, "objsetid", PROP_TYPE_NUMBER,
	    PROP_READONLY, ZFS_TYPE_DATASET, "OBJSETID");
	zprop_register_hidden(ZFS_PROP_INCONSISTENT, "inconsistent",
	    PROP_TYPE_NUMBER, PROP_READONLY, ZFS_TYPE_DATASET, "INCONSISTENT");
	zprop_register_hidden(ZFS_PROP_PREV_SNAP, "prevsnap", PROP_TYPE_STRING,
	    PROP_READONLY, ZFS_TYPE_FILESYSTEM | ZFS_TYPE_VOLUME, "PREVSNAP");

	/* oddball properties */
	zprop_register_impl(ZFS_PROP_CREATION, "creation", PROP_TYPE_NUMBER, 0,
	    NULL, PROP_READONLY, ZFS_TYPE_DATASET | ZFS_TYPE_BOOKMARK,
	    "<date>", "CREATION", B_FALSE, B_TRUE, NULL);
}