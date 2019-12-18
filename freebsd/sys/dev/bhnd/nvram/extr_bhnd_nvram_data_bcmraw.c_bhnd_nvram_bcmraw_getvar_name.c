__attribute__((used)) static const char *
bhnd_nvram_bcmraw_getvar_name(struct bhnd_nvram_data *nv, void *cookiep)
{
	/* Cookie points to key\0value\0 */
	return (cookiep);
}