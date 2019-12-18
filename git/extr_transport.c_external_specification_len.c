__attribute__((used)) static int external_specification_len(const char *url)
{
	return strchr(url, ':') - url;
}