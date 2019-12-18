#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  val ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_2__ {int offset; int length; scalar_t__ val_id; scalar_t__ key_id; } ;
typedef  TYPE_1__ lmo_entry_t ;
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  key ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*) ; 
 int extract_string (char*,char*,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fsync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_index (void*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_uint32 (int,int /*<<< orphan*/ *) ; 
 void* realloc (void*,int) ; 
 scalar_t__ sfh_hash (char*,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char*) ; 
 char* strstr (char*,char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  usage (char*) ; 

int main(int argc, char *argv[])
{
	char line[4096];
	char key[4096];
	char val[4096];
	char tmp[4096];
	int state  = 0;
	int offset = 0;
	int length = 0;
	int n_entries = 0;
	void *array = NULL;
	lmo_entry_t *entry = NULL;
	uint32_t key_id, val_id;

	FILE *in;
	FILE *out;

	if( (argc != 3) || ((in = fopen(argv[1], "r")) == NULL) || ((out = fopen(argv[2], "w")) == NULL) )
		usage(argv[0]);

	memset(line, 0, sizeof(key));
	memset(key, 0, sizeof(val));
	memset(val, 0, sizeof(val));

	while( (NULL != fgets(line, sizeof(line), in)) || (state >= 2 && feof(in)) )
	{
		if( state == 0 && strstr(line, "msgid \"") == line )
		{
			switch(extract_string(line, key, sizeof(key)))
			{
				case -1:
					die("Syntax error in msgid");
				case 0:
					state = 1;
					break;
				default:
					state = 2;
			}
		}
		else if( state == 1 || state == 2 )
		{
			if( strstr(line, "msgstr \"") == line || state == 2 )
			{
				switch(extract_string(line, val, sizeof(val)))
				{
					case -1:
						state = 4;
						break;
					default:
						state = 3;
				}
			}
			else
			{
				switch(extract_string(line, tmp, sizeof(tmp)))
				{
					case -1:
						state = 2;
						break;
					default:
						strcat(key, tmp);
				}
			}
		}
		else if( state == 3 )
		{
			switch(extract_string(line, tmp, sizeof(tmp)))
			{
				case -1:
					state = 4;
					break;
				default:
					strcat(val, tmp);
			}
		}

		if( state == 4 )
		{
			if( strlen(key) > 0 && strlen(val) > 0 )
			{
				key_id = sfh_hash(key, strlen(key));
				val_id = sfh_hash(val, strlen(val));

				if( key_id != val_id )
				{
					n_entries++;
					array = realloc(array, n_entries * sizeof(lmo_entry_t));
					entry = (lmo_entry_t *)array + n_entries - 1;

					if (!array)
						die("Out of memory");

					entry->key_id = key_id;
					entry->val_id = val_id;
					entry->offset = offset;
					entry->length = strlen(val);

					length = strlen(val) + ((4 - (strlen(val) % 4)) % 4);

					print(val, length, 1, out);
					offset += length;
				}
			}

			state = 0;
			memset(key, 0, sizeof(key));
			memset(val, 0, sizeof(val));
		}

		memset(line, 0, sizeof(line));
	}

	print_index(array, n_entries, out);

	if( offset > 0 )
	{
		print_uint32(offset, out);
		fsync(fileno(out));
		fclose(out);
	}
	else
	{
		fclose(out);
		unlink(argv[2]);
	}

	fclose(in);
	return(0);
}